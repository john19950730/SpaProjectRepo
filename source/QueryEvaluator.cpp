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

	/*** TODO: MERGING AND INTERSECTION HERE ***/
	
	// No common synonym
	// One common synonym
	// Two common synonyms
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