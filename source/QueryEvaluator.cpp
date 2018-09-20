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
		return APICall::apiCallForNoClause(synonymType);
	}

	// One such that clause only
	if (queryObject->getNumberOfSuchThatClauses() == 1 && !queryObject->hasPatternClause()) {
		Result* result = evaluateSuchThatClause();
		map < string, vector<string> > selectMap = result->toComparableFormat().first;
		return selectFrom(selectMap);
	}

	// One pattern clause only
	if (queryObject->getNumberOfSuchThatClauses() == 0 && queryObject->hasPatternClause()) {
		Result* result = evaluatePatternClause();
		map < string, vector<string> > selectMap = result->toComparableFormat().first;
		return selectFrom(selectMap);
	}

	// One such that clause and one pattern clause
	if (queryObject->getNumberOfSuchThatClauses() == 1 && queryObject->hasPatternClause()) {
		// TODO: SELECT RESULT HERE OR INSIDE CLAUSE
		Result* result = evaluateSuchThatAndPatternClause();
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

Result* QueryEvaluator::evaluateSuchThatAndPatternClause() {
	// TODO
	Result* suchThatClauseResult = evaluateSuchThatClause();
	Result* patternClauseResult = evaluatePatternClause();

	suchThatClauseResult->printMap();
	patternClauseResult->printMap();

	 map<string, vector<string>> suchThatTable = suchThatClauseResult->toComparableFormat().first;
	 map<string, vector<string>> patternTable = patternClauseResult->toComparableFormat().first;
	 bool isSuchThatClauseValid = suchThatClauseResult->toComparableFormat().second;
	 bool isPatternClauseValid = patternClauseResult->toComparableFormat().second;

	 // For clauses that only return true/false
	 if (!isSuchThatClauseValid || !isPatternClauseValid) {
		 // empty result, bool = false - no results
		 MapBooleanPairResult *result = new MapBooleanPairResult(false);
		 return result;
	 }

	 // Not a true/false clause but returns no results
	 if (isSuchThatClauseValid && isPatternClauseValid && suchThatTable.empty() && patternTable.empty()) {
		 // empty result, bool = true - might still have results after selecting
		 MapBooleanPairResult *result = new MapBooleanPairResult(true);
		 return result;
	 }

	/****
		suchThatClauseResult - pair< map<string, vector<string> >, boolean>
		patternClause - pair< map<string, vector<string> >, boolean>

		BooleanResponse api call returns boolean and not a vector of results, 
		hence, manually we need to return an empty vector with the boolean value.

		E.g.	Uses(1, "v") returns true - pair<emptyMap, true> will be returned
				Modifies(1,"v") returns false - pair(emptyMap, false) will be returned

		1) Check if any of the boolean value is false
			if(any of the boolean value is false) return noResults()

		2) For clauses without synonyms (e.g. Uses(1,"v"), Follows(1,2))
			if(both maps() are empty && both boolean value are true)
				return immediateResults();
			else if(any of the maps are empty && any of the boolean value is false)
				return noResults();

		3) Check if the select synonym is found in any of the synonym between the two clauses
			if(select synonym is not found)
				return immediateResults()

		4) Check if there are commmon synonyms between the two clauses
			if(no common synonym)
			
			else if(two common synonyms)
				get intersection between the two maps

			else if(one common synonym)
		
		5) map of <string, vector<string>> is built

		6) throw to select function to select the synonym accordingly, and return as vector<string>
	******/
	return NULL;
}

vector<string> QueryEvaluator::selectFrom(map < string, vector<string> > selectMap) {
	string selectClause = queryObject->getSelectClause().at(0);
	return selectMap[selectClause];
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