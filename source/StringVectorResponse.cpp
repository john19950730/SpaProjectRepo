#include "StringVectorResponse.h"
#include "Keywords.h"
#include "PKB.h"
#include <vector>

using namespace keywords::clauseParamType;
using namespace keywords::query;

StringVectorResponse::StringVectorResponse() : APICallResponse() {}

string StringVectorResponse::apiCallForFollows() {
	return "";
}
string StringVectorResponse::apiCallForParent() {
	return "";
}
string StringVectorResponse::apiCallForUses() {
	cout << "Uses String Vector" << endl;
	vector<string> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	if (paramType == make_pair(STMT_NO, SYNONYM) || paramType == make_pair(STMT_NO, UNDERSCORE)) {
		return "getAllVariablesUsedByStmtNo(stoi(firstParam))";
		result = PKB::getAllVariablesUsedByStmtNo(stoi(firstParam));
	} 
	else if (paramType == make_pair(PROC_NAME, SYNONYM) || paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		return "getAllVariablesUsedByProcedures(firstParam)";
		result = PKB::getAllVariablesUsedByProcedures(firstParam);
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) {
		if (synonymTable[firstParam] == PROC_VAR) {
			return "getAllProcedureThatUses(secondParam)";
			result = PKB::getAllProcedureThatUses(secondParam);
		}
	}
	return getResults(result);
}

string StringVectorResponse::apiCallForModifies() {
	cout << "Modifies String Vector" << endl;
	vector<string> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	if (paramType == make_pair(STMT_NO, SYNONYM) || paramType == make_pair(STMT_NO, UNDERSCORE)) {
		return "getAllVariablesModifiedByStmtNo(firstParam)";
		result = PKB::getAllVariablesModifiedByStmtNo(stoi(firstParam));
	}
	else if (paramType == make_pair(PROC_NAME, SYNONYM) || paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		return "getAllVariablesModifiedByProcedures(firstParam)";
		result = PKB::getAllVariablesModifiedByProcedures(firstParam);
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) {
		if (synonymTable[firstParam] == PROC_VAR) {
			return "getAllProcedureThatModifies(secondParam)";
			result = PKB::getAllProcedureThatModifies(secondParam);
		}
	}
	return getResults(result);
}

string StringVectorResponse::strVectorToString(vector<string> input) {
	string s = "";
	for (string i : input) {
		s += " " + i;
	}
	return s;
}

string StringVectorResponse::getResults(vector<string> result) {
	if (!result.empty()) {
		if (!selectSynonymIsFoundInParam()) return getImmediateResults();
		else return strVectorToString(result);
	}
	else return getNoResults();
}