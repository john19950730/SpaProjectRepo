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
		cout << "isRsValid = PKB::isFollows(unsigned(stoi(firstParam)), unsigned(stoi(secondParam)), hasTransitiveClosure); // Follows(1, 2)" << endl;
		isRsValid = PKB::isFollows(unsigned(stoi(firstParam)), unsigned(stoi(secondParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		cout << "isRsValid = PKB::hasFollows(unsigned(stoi(firstParam)), hasTransitiveClosure); // Follows(1, _)" << endl;
		isRsValid = PKB::hasFollows(unsigned(stoi(firstParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(UNDERSCORE, STMT_NO)) { 
		cout << "isRsValid = PKB::hasFollowedBy(unsigned(stoi(secondParam)), hasTransitiveClosure); // Follows(_, 2)" << endl;
		isRsValid = PKB::hasFollowedBy(unsigned(stoi(secondParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(UNDERSCORE, UNDERSCORE)) {
		cout << "isRsValid = PKB::hasFollowsPair(hasTransitiveClosure); // Follows(_, _)" << endl;
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
		cout << "isRsValid = PKB::isParent(unsigned(stoi(firstParam)), unsigned(stoi(secondParam)), hasTransitiveClosure); // Parent(1, 2)" << endl;
		isRsValid = PKB::isParent(unsigned(stoi(firstParam)), unsigned(stoi(secondParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		cout << "isRsValid = PKB::hasChild(unsigned(stoi(firstParam)), hasTransitiveClosure); // Parent(1, _)" << endl;
		isRsValid = PKB::hasChild(unsigned(stoi(firstParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(UNDERSCORE, STMT_NO)) { 
		cout << "isRsValid = PKB::hasParent(unsigned(stoi(secondParam)), hasTransitiveClosure); // Parent(_, 2)" << endl;
		isRsValid = PKB::hasParent(unsigned(stoi(secondParam)), hasTransitiveClosure);
	}
	else if (paramType == make_pair(UNDERSCORE, UNDERSCORE)) {
		cout << "isRsValid = PKB::hasParentPair(hasTransitiveClosure); // Parent(_, _)" << endl;
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
		cout << "PKB::isUses(stoi(firstParam), secondParam) // Uses(1, 'var')" << endl;
		isRsValid = PKB::isUses(unsigned(stoi(firstParam)), secondParam);
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) { 
		cout << "PKB::isProcedureUses(firstParam, secondParam) // Uses('proc', 'var')" << endl;
		isRsValid = PKB::isProcedureUses(firstParam, secondParam);
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		cout << "isRsValid = PKB::hasUses(unsigned(stoi(firstParam))) // Uses(1, _)" << endl;
		isRsValid = PKB::hasUses(unsigned(stoi(firstParam)));
	}
	else if (paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		cout << "isRsValid = PKB::hasProcedureUses(firstParam) // Uses('proc', _)";
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
		cout << "PKB::isModifies(stoi(firstParam), secondParam) // Modifies(1, 'var')" << endl;
		isRsValid = PKB::isModifies(unsigned(stoi(firstParam)), secondParam); 
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
		cout << "PKB::isProcedureModifies(firstParam, secondParam) // Modifies('proc', 'var')" << endl;
		isRsValid = PKB::isProcedureModifies(firstParam, secondParam);
	}
	else if (paramType == make_pair(STMT_NO, UNDERSCORE)) {
		cout << "isRsValid = PKB::hasModifies(unsigned(stoi(firstParam))) // Modifies(1, _)" << endl;
		isRsValid = PKB::hasModifies(unsigned(stoi(firstParam)));
	}
	else if (paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		cout << "isRsValid = PKB::hasProcedureModifies(firstParam); // Modifies('proc', _)" << endl;
		isRsValid = PKB::hasProcedureModifies(firstParam);
	}

	BooleanResult *result = new BooleanResult(isRsValid);
	return result;
}