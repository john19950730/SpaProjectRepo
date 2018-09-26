#include "StringVectorResponse.h"
#include "Keywords.h"
#include "PKB.h"
#include <vector>

using namespace keywords::clauseParamType;
using namespace keywords::query;

StringVectorResponse::StringVectorResponse() : APICallSuchThatClause() {}

StringVectorResult* StringVectorResponse::apiCallForFollows() {
	return NULL;	// should throw exception error here
}

StringVectorResult* StringVectorResponse::apiCallForParent() {
	return NULL;	// show throw exception error here
}

StringVectorResult* StringVectorResponse::apiCallForUses() {
	cout << "Uses String Vector" << endl;
	vector<string> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string synonym;
	
	if (paramType == make_pair(STMT_NO, SYNONYM)) {
		result = PKB::getAllVariablesUsedByStmtNo(unsigned(stoi(firstParam))); // Uses(1, v)
		synonym = secondParam;
		cout << "getAllVariablesUsedByStmtNo // Uses(1, v)" << endl;
	}
	else if (paramType == make_pair(PROC_NAME, SYNONYM)) {
		result = PKB::getAllVariablesUsedByProcedure(firstParam);	// Uses("proc" , v)
		synonym = secondParam;
		cout << "getAllVariablesUsedByProcedure // Uses('proc' , v)" << endl;
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		result = PKB::getAllProceduresThatUses(); // Uses(p, _)
		synonym = firstParam;
		cout << "getAllProceduresThatUses // Uses(p, _)" << endl;
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) {
		result = PKB::getAllProceduresThatUsesVariable(secondParam);	// Uses(p, "var")
		synonym = firstParam;
		cout << "getAllProceduresThatUsesVariable // Uses(p, 'var')" << endl;
	}

	StringVectorResult *strVectorResult = new StringVectorResult(result, synonym);
	return strVectorResult;
}

StringVectorResult* StringVectorResponse::apiCallForModifies() {
	cout << "Modifies String Vector" << endl;
	vector<string> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string synonym;
	
	if (paramType == make_pair(STMT_NO, SYNONYM)) {
		result = PKB::getAllVariablesModifiedByStmtNo(unsigned(stoi(firstParam))); // Modifies(1, v)
		synonym = secondParam;
		cout << "getAllVariablesModifiedByStmtNo // Modifies(1, v)" << endl;
	}
	else if (paramType == make_pair(PROC_NAME, SYNONYM)) {
		result = PKB::getAllVariablesModifiedByProcedure(firstParam);	// Modifies("proc" , v)
		synonym = secondParam;
		cout << "getAllVariablesUsedByProcedure // Modifies('proc' , v)" << endl;
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		result = PKB::getAllProceduresThatModifies(); // Modifies(p, _)
		synonym = firstParam;
		cout << "getAllProceduresThatModifies // Modifies(p, _)" << endl;
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) {
		result = PKB::getAllProceduresThatModifiesVariable(secondParam);	// Modifies(p, "var")
		synonym = firstParam;
		cout << "getAllProceduresThatModifiesVariable // Modifies(p, 'var')" << endl;
	}

	StringVectorResult *strVectorResult = new StringVectorResult(result, synonym);
	return strVectorResult;
}