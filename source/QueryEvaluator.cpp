#include "QueryEvaluator.h"
#include "Keywords.h"
#include "Utility.h"
#include "PKB.h"

#include <iostream>

using namespace std;
using namespace keywords::query;

QueryEvaluator::QueryEvaluator(QueryObject *queryObject) {
	this->queryObject = queryObject;
}

string QueryEvaluator::evaluateQueryObject() {
	if (!queryObject->hasClauses()) {
		cout << "No clauses" << endl;
		return selectImmediateResults();
	}


	// First milestone - evaluate only one clause
	if (queryObject->getNumberOfClauses() == 1) return evaluateSingleClause();
	
	return "Error";
}

// Return results immediately if there are no clauses
string QueryEvaluator::selectImmediateResults() {
	vector<string> selectSynonyms = queryObject->getSelectClause();
	
	/*if (varType == ASSIGNMENT_VAR) return "allAssignmentStmts";
	else if (varType == VARIABLE_VAR) return "allVariableStmts";
	else if (varType == STMT_VAR) return "allStmts";
	else if (varType == PROC_VAR) return "allProcedures";*/

	return "";
}

string QueryEvaluator::evaluateSingleClause() {
	if (queryObject->hasUsesClause()) return evaluateUsesClause();
	else if (queryObject->hasModifiesClause()) return evaluateModifiesClause();
	else if (queryObject->hasParentClause()) return evaluateParentClause();
	else if (queryObject->hasFollowsClause()) return evaluateFollowsClause();
}

string QueryEvaluator::evaluateUsesClause() {
	vector<SUCH_THAT_CLAUSE> usesClause = queryObject->getUsesClause();
	vector<SUCH_THAT_CLAUSE>::iterator it;
	/*for (it = usesClause.begin(); it != usesClause.end(); it++) {
		string firstParam = it->firstParameter;
		string secondParam = it->secondParameter;

		if (Utility::isInteger(firstParam)) {
			int stmtNo = stoi(firstParam);
			if(PKB::isUses(stmtNo, secondParam))
		}
	}*/

	//string firstEntity = usesClause.firstParameter; // check if the first parameter is a stmtNo or synonym
	//string variable = usesClause.secondParameter;

	/*if (Utility::isInteger(firstEntity)) {
		int parsedFirstEntity = stoi(firstEntity);
		// return the "select" immediately if its true
		if(PKB::isUses(parsedFirstEntity, variable)) return selectImmediateResults();
		else return ""; // clause is false hence return immediately
	}
	else {
		vector<int> stmtsThatUsesVariable = getStmtsThatUsesVariable(PKB::getAllStmtThatUses(variable)
			, variable);
		if(stmtsThatUsesVariable.size !=0 ) cout << getStmtsThatUsesVariable << endl;
		else return "";
	}*/

	return "";
}

string QueryEvaluator::evaluateModifiesClause() {
	return "";
}

string QueryEvaluator::evaluateParentClause() {
	return "";
}

string QueryEvaluator::evaluateFollowsClause() {
	return "";
}

vector<int> QueryEvaluator::getStmtsThatUsesVariable(vector<int> v, string variable) {
	vector<int>::iterator it;
	vector<int> stmtThatUsesVariable;
	for (it = v.begin(); it != v.end(); it++) {
		if (PKB::isUses(*it, variable)) {
			stmtThatUsesVariable.push_back(*it);
		}
	}
	return stmtThatUsesVariable;
}