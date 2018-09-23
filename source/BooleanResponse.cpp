#include "BooleanResponse.h"
#include "PKB.h"
#include "Keywords.h"
#include <iostream>

using namespace keywords::clauseParamType;

BooleanResponse::BooleanResponse() : APICallSuchThatClause() {}

BooleanResult* BooleanResponse::apiCallForFollows() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	if (paramType == make_pair(STMT_NO, STMT_NO)) {
		//forTesting = "isRsValid = PKB::isFollows(unsigned(stoi(firstParam)), unsigned(stoi(secondParam)), hasTransitiveClosure); // Follows(1, 2)";
		isRsValid = PKB::isFollows(unsigned(stoi(firstParam)), unsigned(stoi(secondParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		//forTesting = "isRsValid = PKB::hasFollows(unsigned(stoi(firstParam)), hasTransitiveClosure); // Follows(1, _)";
		isRsValid = PKB::hasFollows(unsigned(stoi(firstParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(UNDERSCORE, STMT_NO)) { 
		//forTesting = "isRsValid = PKB::hasFollowedBy(unsigned(stoi(secondParam)), hasTransitiveClosure); // Follows(_, 2)";
		isRsValid = PKB::hasFollowedBy(unsigned(stoi(secondParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(UNDERSCORE, UNDERSCORE)) {
		//forTesting = "isRsValid = PKB::hasFollowsPair(hasTransitiveClosure); // Follows(_, _)";
		isRsValid = PKB::hasFollowsPair(hasTransitiveClosure);
	}
	
	BooleanResult *result = new BooleanResult(isRsValid);
	return result;
}

BooleanResult* BooleanResponse::apiCallForParent() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	if (paramType == make_pair(STMT_NO, STMT_NO)) {
		//forTesting = "isRsValid = PKB::isParent(unsigned(stoi(firstParam)), unsigned(stoi(secondParam)), hasTransitiveClosure); // Parent(1, 2)";
		isRsValid = PKB::isParent(unsigned(stoi(firstParam)), unsigned(stoi(secondParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		//forTesting = "isRsValid = PKB::hasChild(unsigned(stoi(firstParam)), hasTransitiveClosure); // Parent(1, _)";
		isRsValid = PKB::hasChild(unsigned(stoi(firstParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(UNDERSCORE, STMT_NO)) { 
		//forTesting = "isRsValid = PKB::hasParent(unsigned(stoi(secondParam)), hasTransitiveClosure); // Parent(_, 2)";
		isRsValid = PKB::hasParent(unsigned(stoi(secondParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(UNDERSCORE, UNDERSCORE)) {
		//forTesting = "isRsValid = PKB::hasParentPair(hasTransitiveClosure); // Parent(_, _)";
		isRsValid = PKB::hasParentPair(hasTransitiveClosure);
	}
	
	BooleanResult *result = new BooleanResult(isRsValid);
	return result;
}

BooleanResult* BooleanResponse::apiCallForUses() {
	cout << "API Call for uses" << endl;
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	
	if (paramType == make_pair(STMT_NO, VARIABLE)) { 
		//forTesting = "PKB::isUses(stoi(firstParam), secondParam) // Uses(1, 'var')";
		isRsValid = PKB::isUses(unsigned(stoi(firstParam)), secondParam);
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) { 
		//forTesting = "PKB::isProcedureUses(firstParam, secondParam) // Uses('proc', 'var')";
		isRsValid = PKB::isProcedureUses(firstParam, secondParam);
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		//forTesting = "isRsValid = PKB::hasUses(unsigned(stoi(firstParam))) // Uses(1, _)"; 
		isRsValid = PKB::hasUses(unsigned(stoi(firstParam)));
	}
	else if (paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		//forTesting = "isRsValid = PKB::hasProcedureUses(firstParam) // Uses('proc', _)";
		isRsValid = PKB::hasProcedureUses(firstParam);
	}

	BooleanResult *result = new BooleanResult(isRsValid);
	return result;
}

BooleanResult* BooleanResponse::apiCallForModifies() {
	bool isRsValid = false;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	
	if (paramType == make_pair(STMT_NO, VARIABLE)) {
		//forTesting = "PKB::isModifies(stoi(firstParam), secondParam) // Modifies(1, 'var')";
		isRsValid = PKB::isModifies(unsigned(stoi(firstParam)), secondParam); 
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
		//forTesting = "PKB::isProcedureModifies(firstParam, secondParam) // Modifies('proc', 'var')"; 
		isRsValid = PKB::isProcedureModifies(firstParam, secondParam);
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		//forTesting = "isRsValid = PKB::hasModifies(unsigned(stoi(firstParam))) // Modifies(1, _)"; 
		isRsValid = PKB::hasModifies(unsigned(stoi(firstParam)));
	}
	else if (paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		//forTesting = "isRsValid = PKB::hasProcedureModifies(firstParam); // Modifies('proc', _)";
		isRsValid = PKB::hasProcedureModifies(firstParam);
	}

	BooleanResult *result = new BooleanResult(isRsValid);
	return result;
}