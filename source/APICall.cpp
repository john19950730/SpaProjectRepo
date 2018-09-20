#include "APICall.h"
#include "Keywords.h"

using namespace keywords::query;

vector<string> APICall::apiCallForImmediateResults(string synonymType) {
	return immediateResults(synonymType);
}

vector<string> APICall::apiCallForNoResults() {
	return vector<string>();
}

vector<string> APICall::getImmediateResults() {
	return vector<string>();
	string synonymType = synonymTable[selectSynonym];
	return immediateResults(synonymType);
}

vector<string> APICall::getNoResults() {
	return vector<string>();
}

vector<string> APICall::immediateResults(string synonymType) {
	vector<string> results;

	if (synonymType == ASSIGNMENT_VAR) results.push_back("allAssignmentStmts");
	else if (synonymType == VARIABLE_VAR) results.push_back("allVariableStmts");
	else if (synonymType == STMT_VAR) results.push_back("allStmts");
	else if (synonymType == PROC_VAR) results.push_back("allProcedures");
	else if (synonymType == IF_VAR) results.push_back("allIfStmts");
	else if (synonymType == WHILE_VAR) results.push_back("allWhileStmts");
	else if (synonymType == READ_VAR) results.push_back("allReadStmts");
	else if (synonymType == PRINT_VAR) results.push_back("allPrintStmts");

	return results;
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