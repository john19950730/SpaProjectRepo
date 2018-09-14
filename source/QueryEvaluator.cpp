#include "QueryEvaluator.h"
#include "Keywords.h"
#include "Utility.h"
#include "PKB.h"

#include <iostream>

using namespace std;
using namespace keywords::query;
using namespace keywords::clauseParamType;

QueryEvaluator::QueryEvaluator(QueryObject *queryObject) {
	this->queryObject = queryObject;
}

string QueryEvaluator::evaluateQueryObject() {
	if (!queryObject->hasClauses()) {
		return selectImmediateResults();
	}

	// First milestone - evaluate only one clause
	if (queryObject->getNumberOfClauses() == 1) return evaluateSingleClause();
	
	return "Error";
}

// Return results immediately if there are no clauses
string QueryEvaluator::selectImmediateResults() {
	string selectSynonym = queryObject->getSelectClause().at(0);	// Only one select synonym for iteration 1
	string synonymType = queryObject->getSynonymTable()[selectSynonym];

	if (synonymType == ASSIGNMENT_VAR) return "allAssignmentStmts";
	else if (synonymType == VARIABLE_VAR) return "allVariableStmts";
	else if (synonymType == STMT_VAR) return "allStmts";
	else if (synonymType == PROC_VAR) return "allProcedures";

	return "";
}

string QueryEvaluator::evaluateSingleClause() {
	if (queryObject->hasUsesClause()) return evaluateUsesClause();
	else if (queryObject->hasModifiesClause()) return evaluateModifiesClause();
	else if (queryObject->hasParentClause()) return evaluateParentClause();
	else if (queryObject->hasFollowsClause()) return evaluateFollowsClause();
}

string QueryEvaluator::evaluateUsesClause() {
	SUCH_THAT_CLAUSE useClause = queryObject->getUsesClause().at(0);

	// Extract the clause information
	map<string, string> synonymTable = queryObject->getSynonymTable();
	string firstParam = useClause.firstParameter;
	string secondParam = useClause.secondParameter;
	pair<string, string> paramType = getParamType(useClause);
	
	if (paramType == make_pair(STMT_NO, SYNONYM) || paramType == make_pair(STMT_NO, UNDERSCORE)) {
		return "getAllVariablesUsedBy(int stmtNo)";
	}
	else if (paramType == make_pair(STMT_NO, VARIABLE)) {
		if (PKB::isUses(stoi(firstParam), secondParam)) return noResult();
		else return selectImmediateResults();
	} 
	else if (paramType == make_pair(PROC_NAME, SYNONYM) || paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		return "getAllProceduresUsedBy(string proc_name)";
	}
	else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
		return "isProcUses(string proc_name, string variable)";
	} 
	else if (paramType == make_pair(SYNONYM, SYNONYM) || paramType == make_pair(SYNONYM, UNDERSCORE)) {
		if (synonymTable[firstParam] == ASSIGNMENT_VAR) return "getAllAssignmentUsesVariablePairs()";
		else if (synonymTable[firstParam] == STMT_VAR) return "getAllStmtUsesVariablePairs()";
		else if (synonymTable[firstParam] == PROC_VAR) return "getAllProcedureUsesVariablePairs()";

		return "";
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) {
		if (synonymTable[firstParam] == ASSIGNMENT_VAR) return "getAllAssignmentThatUsesVariable(string variable)";
		else if (synonymTable[firstParam] == STMT_VAR) return "getAllStmtThatUsesVariable(string variable)";
		else if (synonymTable[firstParam] == PROC_VAR) return " getAllProcedureThatUsesVariable(string variable)";

		return "";
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

string QueryEvaluator::selectIntermediateResult(vector<string> result, SUCH_THAT_CLAUSE clause) {
	// Extract the clause information
	map<string, string> synonymTable = queryObject->getSynonymTable();
	string firstParam = clause.firstParameter;
	string secondParam = clause.secondParameter;

	// Synonym not found - return select immediate results
	if (synonymTable.find(firstParam) != synonymTable.end()
		&& synonymTable.find(secondParam) != synonymTable.end()) {
		return selectImmediateResults();
	}

	string selectClause = queryObject->getSelectClause().at(0);

	pair<string, string> paramType = getParamType(clause);
	if (getParamType(clause) == make_pair(SYNONYM, SYNONYM)) {
		if(firstParam == selectClause)
		else if(secondParam == selectClause)
	}
	else if (getParamType(clause) == make_pair(SYNONYM, VARIABLE)) {

	}
	else if (getParamType(clause) == make_pair(VARIABLE, SYNONYM)) {

	}

	// Synonym found in param 1

	// Synonym found
	
}

string QueryEvaluator::noResult() {
	return "";
}