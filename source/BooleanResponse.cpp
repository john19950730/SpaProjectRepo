#include "BooleanResponse.h"
#include "PKB.h"
#include "Keywords.h"
#include <iostream>

using namespace keywords::clauseParamType;

BooleanResponse::BooleanResponse() : APICallResponse() {}

string BooleanResponse::apiCallForFollows() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	return "PKB::isFollows(stoi(firstParam), stoi(secondParam), hasTransitiveClosure)";
	isRsValid = PKB::isFollows(stoi(firstParam), stoi(secondParam), hasTransitiveClosure);

	string result = isRsValid ? getImmediateResults() : getNoResults();
	return result;
}

string BooleanResponse::apiCallForParent() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	return "PKB::isParent(stoi(firstParam), stoi(secondParam), hasTransitiveClosure)";
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
		return "PKB::isUses(stoi(firstParam), secondParam)";
		isRsValid = PKB::isUses(stoi(firstParam), secondParam);
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
		return "PKB::isProcUses(stoi(firstParam), secondParam)";
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
		return "PKB::isModifies(stoi(firstParam), secondParam)";
		isRsValid = PKB::isModifies(stoi(firstParam), secondParam);
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
		return "PKB::isProcModifies(stoi(firstParam), secondParam)";
	}

	string result = isRsValid ? getImmediateResults() : getNoResults();
	return result;
}