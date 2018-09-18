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
	string forTesting;

	if (paramType == make_pair(STMT_NO, STMT_NO)) {
		forTesting = "isRsValid = PKB::isFollows(unsigned(stoi(firstParam)), unsigned(stoi(secondParam)), hasTransitiveClosure); // Follows(1, 2)";
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		forTesting = "isRsValid = PKB::hasFollows(unsigned(stoi(firstParam)), hasTransitiveClosure); // Follows(1, _)";
	}
	else if (paramType == make_pair(UNDERSCORE, STMT_NO)) { 
		forTesting = "isRsValid = PKB::hasFollowedBy(unsigned(stoi(secondParam)), hasTransitiveClosure); // Follows(_, 2)";
	}
	else if (paramType == make_pair(UNDERSCORE, UNDERSCORE)) {
		forTesting = "isRsValid = PKB::hasFollowsPair(hasTransitiveClosure); // Follows(_, _)";
	}
	
	vector<string> result; //= isRsValid ? getImmediateResults() : getNoResults();
	result.push_back(forTesting);
	return result;
}

vector<string> BooleanResponse::apiCallForParent() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;
	string forTesting;

	if (paramType == make_pair(STMT_NO, STMT_NO)) {
		forTesting = "isRsValid = PKB::isParent(unsigned(stoi(firstParam)), unsigned(stoi(secondParam)), hasTransitiveClosure); // Parent(1, 2)";
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		forTesting = "isRsValid = PKB::hasChild(unsigned(stoi(firstParam)), hasTransitiveClosure); // Parent(1, _)";
	}
	else if (paramType == make_pair(UNDERSCORE, STMT_NO)) { 
		forTesting = "isRsValid = PKB::hasParent(unsigned(stoi(secondParam)), hasTransitiveClosure); // Parent(_, 2)";
	}
	else if (paramType == make_pair(UNDERSCORE, UNDERSCORE)) {
		forTesting = "isRsValid = PKB::hasParentPair(hasTransitiveClosure); // Parent(_, _)";
	}
	
	vector<string> result; // = isRsValid ? getImmediateResults() : getNoResults();
	result.push_back(forTesting);
	return result;
}

vector<string> BooleanResponse::apiCallForUses() {
	cout << "API Call for uses" << endl;
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string forTesting;
	
	if (paramType == make_pair(STMT_NO, VARIABLE)) { 
		forTesting = "PKB::isUses(stoi(firstParam), secondParam) // Uses(1, 'var')";
		//isRsValid = PKB::isUses(unsigned(stoi(firstParam)), secondParam);
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) { 
		forTesting = "PKB::isProcedureUses(firstParam, secondParam) // Uses('proc', 'var')";
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		forTesting = "isRsValid = PKB::hasUses(unsigned(stoi(firstParam))) // Uses(1, _)"; 
	}
	else if (paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		forTesting = "isRsValid = PKB::hasProcedureUses(firstParam) // Uses('proc', _)";
	}

	vector<string> result; // isRsValid ? getImmediateResults() : getNoResults();
	result.push_back(forTesting);
	return result;
}

vector<string> BooleanResponse::apiCallForModifies() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string forTesting = "hello";

	if (paramType == make_pair(STMT_NO, VARIABLE)) {
		forTesting = "PKB::isModifies(stoi(firstParam), secondParam) // Modifies(1, 'var')";
		//isRsValid = PKB::isModifies(unsigned(stoi(firstParam)), secondParam); 
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
		forTesting = "PKB::isProcedureModifies(firstParam, secondParam) // Modifies('proc', 'var')"; 
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		forTesting = "isRsValid = PKB::hasModifies(unsigned(stoi(firstParam))) // Modifies(1, _)"; 
	}
	else if (paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		forTesting = "isRsValid = PKB::hasProcedureModifies(firstParam); // Modifies('proc', _)";
	}

	vector<string> result; // isRsValid ? getImmediateResults() : getNoResults();
	result.push_back(forTesting);
	return result;
}