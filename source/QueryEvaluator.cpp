#include "QueryEvaluator.h"
#include "Keywords.h"

#include <iostream>

using namespace std;
using namespace keywords::query;

string QueryEvaluator::evaluateQueryObject(QueryObject *queryObject) {
	SELECT_VAR_CLAUSE *selectClause = queryObject->getSelectClause();
	string varName = selectClause->variableName;
	string varType = selectClause->variableType;

	// Return results immediately if there are no clauses
	if (!queryObject->hasClauses()) {
		if (varType == ASSIGNMENT_VAR) return "allAssignmentStmts";
		else if (varType == VARIABLE_VAR) return "allVariableStmts";
		else if (varType == STMT_VAR) return "allStmts";
		else if (varType == PROC_VAR) return "allProcedures";
	}

	return "";
}