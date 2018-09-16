#include "APICallResponse.h"
#include "BooleanResponse.h"
#include "IntVectorResponse.h"
#include "StringVectorResponse.h"
#include "IntIntPairVectorResponse.h"
#include "IntStringPairVectorResponse.h";
#include "StringStringPairVectorResponse.h"
#include "Keywords.h"

#include <iostream>

using namespace keywords::query;
using namespace keywords::clauseParamType;

APICallResponse::APICallResponse() {}

APICallResponse::APICallResponse(string typeOfRs, pair<string, string> paramType, SUCH_THAT_CLAUSE suchThatClause,
	string selectSynonym, map<string, string> synonymTable) {
	this->typeOfRs = typeOfRs;
	this->paramType = paramType;
	this->suchThatClause = suchThatClause;
	this->selectSynonym = selectSynonym;
	this->synonymTable = synonymTable;
}

void APICallResponse::setTypeOfRs(string typeOfRs) {
	this->typeOfRs = typeOfRs;
}
void APICallResponse::setParamType(pair<string, string> paramType) {
	this->paramType = paramType;
}
void APICallResponse::setSuchThatClause(SUCH_THAT_CLAUSE suchThatClause) {
	this->suchThatClause = suchThatClause;
}
void APICallResponse::setSelectSynonym(string selectSynonym) {
	this->selectSynonym = selectSynonym;
}
void APICallResponse::setSynonymTable(map<string, string> synonymTable) {
	this->synonymTable = synonymTable;
}

string APICallResponse::executeApiCall() {
	if (typeOfRs == USES_RS)
		return apiCallForUses();
	else if (typeOfRs == MODIFIES_RS)
		return apiCallForModifies();
	else if (typeOfRs == FOLLOWS_RS)
		return apiCallForFollows();
	else if (typeOfRs == PARENT_RS)
		return apiCallForParent();
	else
		return "";
}

string APICallResponse::executeApiCallForNoClauses(string synonymType) {
	return apiCallForNoClause(synonymType);
}

string APICallResponse::getImmediateResults() {
	string synonymType = synonymTable[selectSynonym];
	return apiCallForNoClause(synonymType);
}

string APICallResponse::getNoResults() {
	return "";
}

string APICallResponse::apiCallForNoClause(string synonymType) {
	if (synonymType == ASSIGNMENT_VAR) return "allAssignmentStmts";
	else if (synonymType == VARIABLE_VAR) return "allVariableStmts";
	else if (synonymType == STMT_VAR) return "allStmts";
	else if (synonymType == PROC_VAR) return "allProcedures";
	else if (synonymType == IF_VAR) return "allIfStmts";
	else if (synonymType == WHILE_VAR) return "allWhileStmts";
	else if (synonymType == READ_VAR) return "allReadStmts";
	else if (synonymType == PRINT_VAR) return "allPrintStmts";

	return "";
}

APICallResponse* APICallResponse::getApiCallResponse(string typeOfRs, pair<string, string> paramType, 
	SUCH_THAT_CLAUSE suchThatClause, string selectSynonym, map<string, string> synonymTable) {	
	
	map<string, map<pair<string, string>, APICallResponse*>> functionMap = buildFunctionMap(suchThatClause, synonymTable);
	APICallResponse* responseType = functionMap[typeOfRs][paramType];
	
	responseType->setTypeOfRs(typeOfRs);
	responseType->setParamType(paramType);
	responseType->setSuchThatClause(suchThatClause);
	responseType->setSelectSynonym(selectSynonym);
	responseType->setSynonymTable(synonymTable);

	return responseType;
}

bool APICallResponse::selectSynonymIsFoundInParam() {
	return (selectSynonym == suchThatClause.firstParameter || selectSynonym == suchThatClause.secondParameter);
}

bool APICallResponse::underscoreIsFoundInParam() {
	return (paramType.first == UNDERSCORE || paramType.second == UNDERSCORE);
}

bool APICallResponse::synonymIsStatementType(string synonymType) {
	return (synonymType == ASSIGNMENT_VAR || synonymType == STMT_VAR || synonymType == IF_VAR 
		|| synonymType == WHILE_VAR || synonymType == READ_VAR);
}

map<pair<string, string>, APICallResponse*> APICallResponse::buildModifiesUsesMap(SUCH_THAT_CLAUSE suchThatClause, 
	map<string, string> synonymTable) {
	map<pair<string, string>, APICallResponse*> modifiesUsesTable;

	modifiesUsesTable[make_pair(STMT_NO, VARIABLE)] = new BooleanResponse();
	modifiesUsesTable[make_pair(PROC_NAME, VARIABLE)] = new BooleanResponse();
	
	modifiesUsesTable[make_pair(STMT_NO, SYNONYM)] = new StringVectorResponse();
	modifiesUsesTable[make_pair(STMT_NO, UNDERSCORE)] = new StringVectorResponse();
	modifiesUsesTable[make_pair(PROC_NAME, SYNONYM)] = new StringVectorResponse();
	modifiesUsesTable[make_pair(PROC_NAME, UNDERSCORE)] = new StringVectorResponse();
	
	string synonymType = synonymTable[suchThatClause.firstParameter];
	if (synonymIsStatementType(synonymType)) {
		modifiesUsesTable[make_pair(SYNONYM, VARIABLE)] = new IntVectorResponse();
		modifiesUsesTable[make_pair(SYNONYM, SYNONYM)] = new IntStringPairVectorResponse();
		modifiesUsesTable[make_pair(SYNONYM, UNDERSCORE)] = new IntStringPairVectorResponse();
	}
	else {
		modifiesUsesTable[make_pair(SYNONYM, VARIABLE)] = new StringVectorResponse();
		modifiesUsesTable[make_pair(SYNONYM, SYNONYM)] = new StringStringPairVectorResponse();
		modifiesUsesTable[make_pair(SYNONYM, UNDERSCORE)] = new StringStringPairVectorResponse();
	}

	return modifiesUsesTable;
}

map<pair<string, string>, APICallResponse*> APICallResponse::buildFollowsParentMap() {
	map<pair<string, string>, APICallResponse*> followsParentTable;

	followsParentTable[make_pair(STMT_NO, STMT_NO)] = new BooleanResponse();
	
	followsParentTable[make_pair(SYNONYM, STMT_NO)] = new IntVectorResponse();
	followsParentTable[make_pair(UNDERSCORE, STMT_NO)] = new IntVectorResponse();
	followsParentTable[make_pair(STMT_NO, SYNONYM)] = new IntVectorResponse();
	followsParentTable[make_pair(STMT_NO, UNDERSCORE)] = new IntVectorResponse();

	followsParentTable[make_pair(UNDERSCORE, UNDERSCORE)] = new IntIntPairVectorResponse();
	followsParentTable[make_pair(UNDERSCORE, SYNONYM)] = new IntIntPairVectorResponse();
	followsParentTable[make_pair(SYNONYM, UNDERSCORE)] = new IntIntPairVectorResponse();
	followsParentTable[make_pair(SYNONYM, SYNONYM)] = new IntIntPairVectorResponse();

	return followsParentTable;
}

map<string, map<pair<string, string>, APICallResponse*>> APICallResponse::buildFunctionMap(SUCH_THAT_CLAUSE suchThatClause,
	map<string, string> synonymTable) {
	map<string, map<pair<string, string>, APICallResponse*>> functionMap;

	functionMap[USES_RS] = buildModifiesUsesMap(suchThatClause, synonymTable);
	functionMap[MODIFIES_RS] = buildModifiesUsesMap(suchThatClause, synonymTable);
	functionMap[FOLLOWS_RS] = buildFollowsParentMap();
	functionMap[PARENT_RS] = buildFollowsParentMap();

	return functionMap;
}