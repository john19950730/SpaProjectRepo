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
	
	string forTesting;
	vector<string> results;

	if (paramType == make_pair(STMT_NO, SYNONYM)) {
		//result = PKB::getAllVariablesUsedByStmtNo(unsigned(stoi(firstParam))); // Uses(1, v)
		forTesting = "getAllVariablesUsedByStmtNo // Uses(1, v)";
	}
	else if (paramType == make_pair(PROC_NAME, SYNONYM)) {
		//result = PKB::getAllVariablesUsedByProcedure(firstParam);	// Uses("proc" , v)
		forTesting = "getAllVariablesUsedByProcedure // Uses('proc' , v)";
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		//result = PKB::getAllProceduresThatUses(); // Uses(p, _)
		forTesting = "getAllProceduresThatUses // Uses(p, _)";
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) {
		// result = PKB::getAllProceduresThatUsesVariable(secondParam);	// Uses(p, "var")
		forTesting = "getAllProceduresThatUsesVariable // Uses(p, 'var')";
	}

	results.push_back(forTesting);
	return results;
}

vector<string> StringVectorResponse::apiCallForModifies() {
	cout << "Modifies String Vector" << endl;
	vector<string> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	string forTesting;
	vector<string> results;

	if (paramType == make_pair(STMT_NO, SYNONYM)) {
		//result = PKB::getAllVariablesModifiedByStmtNo(unsigned(stoi(firstParam))); // Modifies(1, v)
		forTesting = "getAllVariablesModifiedByStmtNo // Modifies(1, v)";
	}
	else if (paramType == make_pair(PROC_NAME, SYNONYM)) {
		//result = PKB::getAllVariablesModifiedByProcedure(firstParam);	// Modifies("proc" , v)
		forTesting = "getAllVariablesUsedByProcedure // Modifies('proc' , v)";
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		//result = PKB::getAllProceduresThatModifies(); // Modifies(p, _)
		forTesting = "getAllProceduresThatModifies // Modifies(p, _)";
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) {
		//result = PKB::getAllProceduresThatModifiesVariable(secondParam);	// Modifies(p, "var")
		forTesting = "getAllProceduresThatModifiesVariable // Modifies(p, 'var')";
	}

	results.push_back(forTesting);
	return results;
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