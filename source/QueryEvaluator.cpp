#include "QueryEvaluator.h"
#include "Keywords.h"
#include "Utility.h"

#include <iostream>

using namespace std;
using namespace keywords::query;

QueryEvaluator::QueryEvaluator(QueryObject *queryObject) {
	this->queryObject = queryObject;
}

string QueryEvaluator::evaluateQueryObject() {
	if (!queryObject->hasClauses()) return selectImmediateResults();
	
	// First milestone - evaluate only one clause
	if (queryObject->getNumberOfClauses == 1) return evaluateSingleClause();
	
	return "Error";
}

// Return results immediately if there are no clauses
string QueryEvaluator::selectImmediateResults() {
	SELECT_VAR_CLAUSE *selectClause = queryObject->getSelectClause();
	string varName = selectClause->variableName;
	string varType = selectClause->variableType;

	if (varType == ASSIGNMENT_VAR) return "allAssignmentStmts";
	else if (varType == VARIABLE_VAR) return "allVariableStmts";
	else if (varType == STMT_VAR) return "allStmts";
	else if (varType == PROC_VAR) return "allProcedures";

	return "";
}

string QueryEvaluator::evaluateSingleClause() {
	if (queryObject->getUsesClause() != NULL) return evaluateUsesClause();
	else if (queryObject->getModifiesClause() != NULL) return evaluateModifiesClause();
	else if (queryObject->getParentClause() != NULL) return evaluateParentClause();
	else if (queryObject->getFollowsClause() != NULL) return evaluateFollowsClause();
}

string QueryEvaluator::evaluateUsesClause() {
	STMT_PROC_VAR_RS_CLAUSE *usesClause = queryObject->getUsesClause();
	string firstEntity = usesClause->firstEntity; // check if the first parameter is a stmtNo or synonym

	if (Utility::isInteger(firstEntity)) {
		int parsedFirstEntity = stoi(firstEntity);
		string api = "isUses(parsedFirstEntity, varname)"; // check if the clause is true
		return selectImmediateResults(); // return the "select" immediately if its true
	}

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