#include "BooleanResponse.h"
#include "PKB.h"
#include "Keywords.h"
#include <iostream>

using namespace keywords::clauseParamType;

BooleanResponse::BooleanResponse() : APICallSuchThatClause() {}

vector<string> BooleanResponse::apiCallForFollows() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	//isRsValid = PKB::isFollows(stoi(firstParam), stoi(secondParam), hasTransitiveClosure);

	vector<string> result = isRsValid ? getImmediateResults() : getNoResults();
	result.push_back("PKB::isFollows(stoi(firstParam), stoi(secondParam), hasTransitiveClosure)");
	return result;
}

vector<string> BooleanResponse::apiCallForParent() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	isRsValid = PKB::isParent(stoi(firstParam), stoi(secondParam), hasTransitiveClosure);

	vector<string> result = isRsValid ? getImmediateResults() : getNoResults();
	result.push_back("PKB::isParent(stoi(firstParam), stoi(secondParam), hasTransitiveClosure)");
	return result;
}

vector<string> BooleanResponse::apiCallForUses() {
	cout << "API Call for uses" << endl;
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string forTesting;

	if (paramType == make_pair(STMT_NO, VARIABLE)) {
		forTesting = "PKB::isUses(stoi(firstParam), secondParam)";
		//isRsValid = PKB::isUses(stoi(firstParam), secondParam);
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
		forTesting = "PKB::isProcUses(stoi(firstParam), secondParam)";
	}

	vector<string> result = isRsValid ? getImmediateResults() : getNoResults();
	result.push_back(forTesting);
	return result;
}

vector<string> BooleanResponse::apiCallForModifies() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string forTesting;

	if (paramType == make_pair(STMT_NO, VARIABLE)) {
		forTesting = "PKB::isModifies(stoi(firstParam), secondParam)";
		isRsValid = PKB::isModifies(stoi(firstParam), secondParam);
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
		forTesting = "PKB::isProcModifies(stoi(firstParam), secondParam)";
	}

	vector<string> result = isRsValid ? getImmediateResults() : getNoResults();
	result.push_back(forTesting);
	return result;
}