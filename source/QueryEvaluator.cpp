#include "QueryEvaluator.h"
#include "Keywords.h"
#include "Utility.h"
#include "PKB.h"
#include "APICallResponse.h";

#include <iostream>

using namespace std;
using namespace keywords::query;
using namespace keywords::clauseParamType;

QueryEvaluator::QueryEvaluator(QueryObject *queryObject) {
	this->queryObject = queryObject;
}

string QueryEvaluator::evaluateQueryObject() {
	if (!queryObject->hasClauses()) {
		string synonymType = queryObject->getSynonymTable()[queryObject->getSelectClause().at(0)];
		return APICallResponse::executeApiCallForNoClauses(synonymType);
	}

	if (queryObject->getNumberOfSuchThatClauses() == 1) {
		return evaluateSingleClause();
	}

	return "Error";
}

string QueryEvaluator::evaluateSingleClause() {
	string selectClause = queryObject->getSelectClause().at(0);
	map<string, string> synonymTable = queryObject->getSynonymTable();

	APICallResponse* apiCallResponse;
	SUCH_THAT_CLAUSE clause;
	string typeOfRs;

	if (queryObject->hasUsesClause()) {
		cout << "Uses" << endl;
		clause = queryObject->getUsesClause().at(0);
		typeOfRs = USES_RS;
	}
	else if (queryObject->hasModifiesClause()) {
		cout << "Modifies" << endl;
		clause = queryObject->getModifiesClause().at(0);
		typeOfRs = MODIFIES_RS;
	}
	else if (queryObject->hasParentClause()) {
		cout << "Parent" << endl;
		clause = queryObject->getParentClause().at(0);
		typeOfRs = PARENT_RS;
	}
	else if (queryObject->hasFollowsClause()) {
		cout << "Follows" << endl;
		clause = queryObject->getFollowsClause().at(0);
		typeOfRs = FOLLOWS_RS;
	}

	apiCallResponse = APICallResponse::getApiCallResponse(typeOfRs, getParamType(clause), clause, selectClause, synonymTable);
	return apiCallResponse->executeApiCall();
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