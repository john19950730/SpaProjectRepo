#include "APICall.h"
#include "Utility.h"
#include "PKB.h"
#include "Keywords.h"

using namespace keywords::query;

vector<string> APICall::apiCallForImmediateResults(string synonymType) {
	return immediateResults(synonymType);
}

vector<string> APICall::apiCallForNoResults() {
	vector<string> result = { "none" };
	return result;
}

vector<string> APICall::getImmediateResults() {
	return vector<string>();
	string synonymType = synonymTable[selectSynonym];
	return immediateResults(synonymType);
}

vector<string> APICall::getNoResults() {
	vector<string> result = { "none" };
	return result;
}

vector<string> APICall::immediateResults(string synonymType) {
	vector<string> test;
	vector<unsigned int> intResults;
	vector<string> strResults;

	if (synonymType == ASSIGNMENT_VAR) {
		cout << "allAssignmentStmts" << endl;
		intResults = PKB::getAssigns();
		return Utility::intVectorToStrVector(intResults);
	}
	else if (synonymType == VARIABLE_VAR) {
		cout << "allVariableStmts" << endl;
		strResults = PKB::getVariables();
		return strResults;
	}
	else if (synonymType == STMT_VAR) {
		cout << "allStmts" << endl;
		intResults = PKB::getAllStmts();
		return Utility::intVectorToStrVector(intResults);
	}
	else if (synonymType == PROC_VAR) {
		cout << "allProcedures" << endl;
		strResults = PKB::getProcedureNames();
		return strResults;
	}
	else if (synonymType == IF_VAR) {
		cout << "allIfStmts" << endl;
		intResults = PKB::getIfs();
		return Utility::intVectorToStrVector(intResults);
	}
	else if (synonymType == WHILE_VAR) {
		cout << "allWhileStmts" << endl;
		intResults = PKB::getWhiles();
		return Utility::intVectorToStrVector(intResults);
	}
	else if (synonymType == READ_VAR) {
		cout << "allReadStmts" << endl;
		intResults = PKB::getReads();
		return Utility::intVectorToStrVector(intResults);
	}
	else if (synonymType == PRINT_VAR) {
		cout << "allPrintStmts" << endl;
		intResults = PKB::getPrints();
		return Utility::intVectorToStrVector(intResults);
	}

	return vector<string>();
}

void APICall::setParamType(pair<string, string> paramType) {
	this->paramType = paramType;
}

void APICall::setSelectSynonym(string selectSynonym) {
	this->selectSynonym = selectSynonym;
}

void APICall::setSynonymTable(map<string, string> synonymTable) {
	this->synonymTable = synonymTable;
}