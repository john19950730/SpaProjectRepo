#include "StringVectorResponse.h"
#include "Keywords.h"
#include "PKB.h"
#include <vector>

using namespace keywords::clauseParamType;
using namespace keywords::query;

StringVectorResponse::StringVectorResponse() : APICallSuchThatClause() {}

vector<string> StringVectorResponse::apiCallForFollows() {
	return vector<string>();	// should throw exception error here
}
vector<string> StringVectorResponse::apiCallForParent() {
	return vector<string>();	// show throw exception error here
}
vector<string> StringVectorResponse::apiCallForUses() {
	cout << "Uses String Vector" << endl;
	vector<string> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	if (paramType == make_pair(STMT_NO, SYNONYM) || paramType == make_pair(STMT_NO, UNDERSCORE)) {
		result.push_back("getAllVariablesUsedByStmtNo(stoi(firstParam))");
		//result = PKB::getAllVariablesUsedByStmtNo(stoi(firstParam));
	} 
	else if (paramType == make_pair(PROC_NAME, SYNONYM) || paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		result.push_back("getAllVariablesUsedByProcedures(firstParam)");
		//result = PKB::getAllVariablesUsedByProcedures(firstParam);
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) {
		if (synonymTable[firstParam] == PROC_VAR) {
			result.push_back("getAllProcedureThatUses(secondParam)");
			//result = PKB::getAllProcedureThatUses(secondParam);
		}
	}
	return getResults(result);
}

vector<string> StringVectorResponse::apiCallForModifies() {
	cout << "Modifies String Vector" << endl;
	vector<string> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	if (paramType == make_pair(STMT_NO, SYNONYM) || paramType == make_pair(STMT_NO, UNDERSCORE)) {
		result.push_back("getAllVariablesModifiedByStmtNo(firstParam)");
		//result = PKB::getAllVariablesModifiedByStmtNo(stoi(firstParam));
	}
	else if (paramType == make_pair(PROC_NAME, SYNONYM) || paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		result.push_back("getAllVariablesModifiedByProcedures(firstParam)");
		//result = PKB::getAllVariablesModifiedByProcedures(firstParam);
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) {
		if (synonymTable[firstParam] == PROC_VAR) {
			result.push_back("getAllProcedureThatModifies(secondParam)");
			//result = PKB::getAllProcedureThatModifies(secondParam);
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

vector<string> StringVectorResponse::getResults(vector<string> result) {
	if (!result.empty()) {
		if (!selectSynonymIsFoundInParam()) return getImmediateResults();
		else return result;
		//else return strVectorToString(result);
	}
	else return getNoResults();
}