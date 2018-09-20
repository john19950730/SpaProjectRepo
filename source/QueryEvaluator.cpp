#include "QueryEvaluator.h"
#include "Keywords.h"
#include "Utility.h"
#include "PKB.h"
#include "APICallSuchThatClause.h"
#include "APICall.h"
#include "APICallPatternClause.h"

#include <iostream>

using namespace std;
using namespace keywords::query;
using namespace keywords::clauseParamType;

QueryEvaluator::QueryEvaluator(QueryObject *queryObject) {
	this->queryObject = queryObject;
}

vector<string> QueryEvaluator::evaluateQueryObject() {
	// No clauses
	if (!queryObject->hasClauses()) {
		string synonymType = queryObject->getSynonymTable()[queryObject->getSelectClause().at(0)];
		return APICall::apiCallForImmediateResults(synonymType);
	}

	// One such that clause only
	if (queryObject->getNumberOfSuchThatClauses() == 1 && !queryObject->hasPatternClause()) {
		return getResults(evaluateSuchThatClause());
	}

	// One pattern clause only
	if (queryObject->getNumberOfSuchThatClauses() == 0 && queryObject->hasPatternClause()) {
		return getResults(evaluatePatternClause());
	}

	// One such that clause and one pattern clause
	if (queryObject->getNumberOfSuchThatClauses() == 1 && queryObject->hasPatternClause()) {
		return getResults(evaluateSuchThatClause(), evaluatePatternClause());
	}

	return vector<string>();
}

Result* QueryEvaluator::evaluateSuchThatClause() {
	string selectClause = queryObject->getSelectClause().at(0);
	map<string, string> synonymTable = queryObject->getSynonymTable();

	APICallSuchThatClause* apiCallResponse;
	SUCH_THAT_CLAUSE clause;
	string typeOfRs;

	if (queryObject->hasUsesClause()) {
		clause = queryObject->getUsesClause().at(0);
		typeOfRs = USES_RS;
	}
	else if (queryObject->hasModifiesClause()) {
		clause = queryObject->getModifiesClause().at(0);
		typeOfRs = MODIFIES_RS;
	}
	else if (queryObject->hasParentClause()) {
		clause = queryObject->getParentClause().at(0);
		typeOfRs = PARENT_RS;
	}
	else if (queryObject->hasFollowsClause()) {
		clause = queryObject->getFollowsClause().at(0);
		typeOfRs = FOLLOWS_RS;
	}

	apiCallResponse = APICallSuchThatClause::getApiCallResponse(typeOfRs, getParamType(clause), clause, selectClause, synonymTable);
	return apiCallResponse->executeApiCall();
}

Result* QueryEvaluator::evaluatePatternClause() {
	PATTERN_CLAUSE patternClause = queryObject->getPatternClause().at(0);
	APICallPatternClause *apiCallPatternClause = new APICallPatternClause(getParamType(patternClause),
		patternClause, queryObject->getSelectClause().at(0), queryObject->getSynonymTable());
	return apiCallPatternClause->executeApiCall();
}

vector<string> QueryEvaluator::getResults(Result* firstResult, Result* secondResult) {
	string selectSynonym = queryObject->getSelectClause().at(0);
	string synonymType = queryObject->getSynonymTable()[selectSynonym];

	map<string, vector<string>> firstResultTable = firstResult->toComparableFormat().first;
	map<string, vector<string>> secondResultTable = secondResult->toComparableFormat().first;

	bool isFirstClauseValid = firstResult->toComparableFormat().second;
	bool isSecondClauseValid = secondResult->toComparableFormat().second;

	// For clauses that returns false or clauses that returns no results
	if (!isFirstClauseValid || !isSecondClauseValid) {
		return APICall::apiCallForNoResults();
	}

	// Both clauses are boolean response which returns true
	if (firstResultTable.empty() && secondResultTable.empty()) {
		return APICall::apiCallForImmediateResults(synonymType);
	}

	// Both clauses have results but select synonym is not found in any of the clause
	if (!firstResult->isSelectSynonymFound(selectSynonym) && !secondResult->isSelectSynonymFound(selectSynonym)) {
		return APICall::apiCallForImmediateResults(synonymType);
	}

	/*** MERGING AND INTERSECTION HERE ***/
	return combineResults(firstResult, secondResult);
}

vector<string> QueryEvaluator::getResults(Result* result) {
	string selectSynonym = queryObject->getSelectClause().at(0);
	string synonymType = queryObject->getSynonymTable()[selectSynonym];
	map < string, vector<string> > selectMap = result->toComparableFormat().first;
	bool isClauseValid = result->toComparableFormat().second;

	result->printMap();

	// Case 1: Clause returns false or Clause has no results
	if (!isClauseValid) {
		cout << "Case 1: Clause returns false or Clause has no results" << endl;
		return APICall::apiCallForNoResults();
	}

	// Case 2: Clause is Boolean Response that returns true
	if (selectMap.empty()) {
		cout << " Case 2: Clause is Boolean Response that returns true" << endl;
		return APICall::apiCallForImmediateResults(synonymType);
	}

	// Case 3: Clause has results but select synonym is not found in the clause
	if (!result->isSelectSynonymFound(selectSynonym)) {
		cout << "Case 3: Clause has results but select synonym is not found in the clause" << endl;
		return APICall::apiCallForImmediateResults(synonymType);
	}
	
	// Case 4: Clause has results and select synonym is found in the clause
	cout << "Case 4: Clause has results and select synonym is found in the clause" << endl;
	return selectFrom(selectMap);
}

vector<string> QueryEvaluator::selectFrom(map < string, vector<string> > selectMap) {
	string selectSynonym = queryObject->getSelectClause().at(0);
	return selectMap[selectSynonym];
}

vector<string> QueryEvaluator::combineResults(Result* firstResult, Result* secondResult) {
	vector<string> firstResultKeys = firstResult->getSynonyms();
	vector<string> secondResultKeys = secondResult->getSynonyms();

	vector<string> commonKeys;
	sort(firstResultKeys.begin(), firstResultKeys.end());
	sort(secondResultKeys.begin(), secondResultKeys.end());

	set_intersection(firstResultKeys.begin(), firstResultKeys.end(),
		secondResultKeys.begin(), secondResultKeys.end(), back_inserter(commonKeys));

	if (commonKeys.empty()) { // No common synonym
		return noCommonSynonym(firstResult, secondResult);
	}
	else if (commonKeys.size() == 1) { // One common synonym
		return oneCommonSynonym(firstResult, secondResult, commonKeys);
	}
	else {	// Two common synonyms
		return twoCommonSynonyms(firstResult, secondResult, commonKeys);
	}
}

vector<string> QueryEvaluator::noCommonSynonym(Result* firstResult, Result* secondResult) {
	string selectSynonym = queryObject->getSelectClause().at(0);
	map<string, vector<string>> firstResultTable = firstResult->toComparableFormat().first;
	map<string, vector<string>> secondResultTable = secondResult->toComparableFormat().first;

	cout << "No common synonyms" << endl;
	if (firstResult->isSelectSynonymFound(selectSynonym)) {	// Select synonym found in first table - Select from first table
		return selectFrom(firstResultTable);
	}
	else { // Select synonym found in second table - Select from second table
		return selectFrom(secondResultTable);
	}
}

vector<string> QueryEvaluator::oneCommonSynonym(Result* firstResult, Result* secondResult, vector<string> commonKeys) {
	string commonKey = commonKeys.at(0);
	vector<string> firstResultKeys = firstResult->getSynonyms();
	vector<string> secondResultKeys = secondResult->getSynonyms();
	map<string, vector<string>> firstResultTable = firstResult->toComparableFormat().first;
	map<string, vector<string>> secondResultTable = secondResult->toComparableFormat().first;

	int totalSynonyms = firstResultKeys.size() + secondResultKeys.size();
	vector<string> firstTableValue = firstResultTable[commonKey];
	vector<string> secondTableValue = secondResultTable[commonKey];
	
	map<string, vector<string>> finalResultsTable;

	if (totalSynonyms == 2) {
		cout << "One common synonym - Total Syn = 2" << endl;
		vector<string> commonValues;
		sort(firstTableValue.begin(), firstTableValue.end());
		sort(secondTableValue.begin(), secondTableValue.end());

		set_intersection(firstTableValue.begin(), firstTableValue.end(),
			secondTableValue.begin(), secondTableValue.end(), back_inserter(commonValues));

		if (commonValues.empty()) {
			return APICall::apiCallForNoResults();
		}

		finalResultsTable[commonKey] = commonValues;
		return selectFrom(finalResultsTable);
	}
	else if (totalSynonyms == 3) {
		cout << "One common synonym - Total Syn = 3" << endl;
		map<string, vector<string>> tableWithTwoSynonyms = firstResultKeys.size() == 2
			? firstResultTable : secondResultTable;

		map<string, vector<string>> tableWithOneSynonym = firstResultKeys.size() == 1
			? firstResultTable : secondResultTable;

		vector<string> tableWithTwoSynonymValue = tableWithTwoSynonyms[commonKey];
		vector<string> tableWithOneSynonymValue = tableWithOneSynonym[commonKey];

		string tableWithTwoSynonymSecondKey;

		if (firstResultKeys.size() == 2) {
			tableWithTwoSynonymSecondKey = firstResultKeys.at(0) != commonKey
				? firstResultKeys.at(0) : firstResultKeys.at(1);
		}
		else {
			tableWithTwoSynonymSecondKey = secondResultKeys.at(0) != commonKey
				? secondResultKeys.at(0) : secondResultKeys.at(1);
		}
		vector<string> tableWithTwoSynonymSecondValue = tableWithTwoSynonyms[tableWithTwoSynonymSecondKey];

		bool isTableEmpty = true;
		vector<string> finalResultCommon;
		vector<string> finalResultSecondValue;

		int pos = 0;
		for (string s : tableWithTwoSynonymValue) {
			vector<string>::iterator it = find(secondTableValue.begin(), secondTableValue.end(), s);
			// String found
			if (it != secondTableValue.end()) {
				finalResultCommon.push_back(s);
				finalResultSecondValue.push_back(tableWithTwoSynonymSecondValue.at(pos));
				isTableEmpty = false;
			}
		}
		if (isTableEmpty) {
			return APICall::apiCallForNoResults();
		}

		finalResultsTable[commonKey] = finalResultCommon;
		finalResultsTable[tableWithTwoSynonymSecondKey] = finalResultSecondValue;
		return selectFrom(finalResultsTable);
	}
	else if (totalSynonyms == 4) {
		cout << "One common synonym - Total Syn = 4" << endl;
		string firstResultSecondKey = firstResultKeys.at(0) != commonKey ? firstResultKeys.at(0) : firstResultKeys.at(1);
		vector<string> firstTableSecondValue = firstResultTable[firstResultSecondKey];

		string secondResultSecondKey = secondResultKeys.at(0) != commonKey ? secondResultKeys.at(0) : secondResultKeys.at(1);
		vector<string> secondTableSecondValue = secondResultTable[secondResultSecondKey];

		bool isTableEmpty = true;
		vector<string> finalResultCommon;
		vector<string> finalResultFirstTableSecondValue;
		vector<string> finalResultSecondTableSecondValue;

		int pos = 0;
		for (string s : firstTableValue) {
			vector<string>::iterator it = find(secondTableValue.begin(), secondTableValue.end(), s);
			// String found
			if (it != secondTableValue.end()) {
				int index = distance(secondTableValue.begin(), it);
				finalResultCommon.push_back(s);
				finalResultFirstTableSecondValue.push_back(firstTableSecondValue.at(pos));
				finalResultSecondTableSecondValue.push_back(secondTableSecondValue.at(index));
				isTableEmpty = false;
			}
			pos++;
		}

		if (isTableEmpty) {
			return APICall::apiCallForNoResults();
		}

		finalResultsTable[commonKey] = finalResultCommon;
		finalResultsTable[firstResultSecondKey] = finalResultFirstTableSecondValue;
		finalResultsTable[secondResultSecondKey] = finalResultSecondTableSecondValue;
		return selectFrom(finalResultsTable);
	}
}

vector<string> QueryEvaluator::twoCommonSynonyms(Result* firstResult, Result* secondResult, vector<string> commonKeys) {
	cout << "2 common synonyms" << endl;
	string commonKey1 = commonKeys.at(0);
	string commonKey2 = commonKeys.at(1);
	map<string, vector<string>> firstResultTable = firstResult->toComparableFormat().first;
	map<string, vector<string>> secondResultTable = secondResult->toComparableFormat().first;

	vector<string> firstTableValue1 = firstResultTable[commonKey1];
	vector<string> firstTableValue2 = firstResultTable[commonKey2];
	vector<string> secondTableValue1 = secondResultTable[commonKey1];
	vector<string> secondTableValue2 = secondResultTable[commonKey2];

	bool isTableEmpty = true;
	vector<string> finalResult1;
	vector<string> finalResult2;
	map<string, vector<string>> finalResultsTable;

	// Find the same pairs
	int pos = 0;
	for (string s : firstTableValue1) {
		vector<string>::iterator it = find(secondTableValue1.begin(), secondTableValue1.end(), s);
		// Pair Found
		if (it != secondTableValue1.end()) {
			int index = distance(secondTableValue1.begin(), it);
			if (secondTableValue2.at(index) == firstTableValue2.at(pos)) {
				finalResult1.push_back(s);
				finalResult2.push_back(firstTableValue2.at(pos));
				isTableEmpty = false;
			}
		}
		pos++;
	}

	// After intersection, if table is empty means no result
	if (isTableEmpty) {
		return APICall::apiCallForNoResults();
	}

	finalResultsTable[commonKey1] = finalResult1;
	finalResultsTable[commonKey2] = finalResult2;
	return selectFrom(finalResultsTable);
}

pair<string, string> QueryEvaluator::getParamType(SUCH_THAT_CLAUSE clause) {
	pair<string, string> paramType(SYNONYM, SYNONYM);

	if (!clause.firstParamIsSynonym) {
		Utility::isInteger(clause.firstParameter) ? paramType.first = STMT_NO : paramType.first = PROC_NAME;
	}

	if (!clause.secondParamIsSynonym) {
		Utility::isInteger(clause.secondParameter) ? paramType.second = STMT_NO : paramType.second = VARIABLE;
	}

	if (Utility::isUnderscore(clause.firstParameter)) paramType.first = UNDERSCORE;
	if (Utility::isUnderscore(clause.secondParameter)) paramType.second = UNDERSCORE;

	return paramType;
}

pair<string, string> QueryEvaluator::getParamType(PATTERN_CLAUSE clause) {
	pair<string, string> paramType(SYNONYM, VARIABLE);
	
	if (!clause.firstParamIsSynonym) {
		paramType.first = VARIABLE;
	}

	if (Utility::isUnderscore(clause.firstParam)) paramType.first = UNDERSCORE;
	if (Utility::isUnderscore(clause.secondParam)) paramType.second = UNDERSCORE;

	if (Utility::isInteger(clause.secondParam)) paramType.second = CONSTANT;

	return paramType;
}