#include "BooleanResponse.h"
#include "PKB.h"
#include "Keywords.h"
#include <iostream>

using namespace keywords::clauseParamType;

BooleanResponse::BooleanResponse() : APICallResponse() {
}

BooleanResponse::BooleanResponse(string typeOfRs, pair<string, string> paramType, SUCH_THAT_CLAUSE suchThatClause, 
	string selectSynonym, map<string, string> synonymTable) 
	: APICallResponse(typeOfRs, paramType, suchThatClause, selectSynonym, synonymTable) {}

string BooleanResponse::apiCallForFollows() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	isRsValid = PKB::isFollows(stoi(firstParam), stoi(secondParam), hasTransitiveClosure);

	string result = isRsValid ? getImmediateResults() : getNoResults();
	return result;
}

string BooleanResponse::apiCallForParent() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	isRsValid = PKB::isParent(stoi(firstParam), stoi(secondParam), hasTransitiveClosure);

	string result = isRsValid ? getImmediateResults() : getNoResults();
	return result;
}

string BooleanResponse::apiCallForUses() {
	cout << "API Call for uses" << endl;
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	if (paramType == make_pair(STMT_NO, VARIABLE)) {
		isRsValid = PKB::isUses(stoi(firstParam), secondParam);
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
		cout << "Proc uses name" << endl;
		return "";
	}

	string result = isRsValid ? getImmediateResults() : getNoResults();
	return result;
}

string BooleanResponse::apiCallForModifies() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	if (paramType == make_pair(STMT_NO, VARIABLE)) {
		isRsValid = PKB::isModifies(stoi(firstParam), secondParam);
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
		cout << "Proc modifies name" << endl;
		return "";
	}

	string result = isRsValid ? getImmediateResults() : getNoResults();
	return result;
}