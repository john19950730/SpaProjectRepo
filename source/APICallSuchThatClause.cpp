#include "APICallSuchThatClause.h"
#include "BooleanResponse.h"
#include "IntVectorResponse.h"
#include "StringVectorResponse.h"
#include "IntIntPairVectorResponse.h"
#include "IntStringPairVectorResponse.h"
#include "StringStringPairVectorResponse.h"
#include "Keywords.h"

#include <iostream>

using namespace keywords::query;
using namespace keywords::clauseParamType;

APICallSuchThatClause::APICallSuchThatClause() {}

void APICallSuchThatClause::setTypeOfRs(string typeOfRs) {
	this->typeOfRs = typeOfRs;
}

void APICallSuchThatClause::setSuchThatClause(SUCH_THAT_CLAUSE suchThatClause) {
	this->suchThatClause = suchThatClause;
}

Result* APICallSuchThatClause::executeApiCall() {
	if (typeOfRs == USES_RS)
		return apiCallForUses();
	else if (typeOfRs == MODIFIES_RS)
		return apiCallForModifies();
	else if (typeOfRs == FOLLOWS_RS)
		return apiCallForFollows();
	else if (typeOfRs == PARENT_RS)
		return apiCallForParent();
	else
		return NULL;
}

APICallSuchThatClause* APICallSuchThatClause::getApiCallResponse(string typeOfRs, pair<string, string> paramType, 
	SUCH_THAT_CLAUSE suchThatClause, string selectSynonym, map<string, string> synonymTable) {	
	
	map<string, map<pair<string, string>, APICallSuchThatClause*>> functionMap = buildFunctionMap(suchThatClause, synonymTable);
	APICallSuchThatClause* responseType = functionMap[typeOfRs][paramType];
	
	responseType->setTypeOfRs(typeOfRs);
	responseType->setParamType(paramType);
	responseType->setSuchThatClause(suchThatClause);
	responseType->setSelectSynonym(selectSynonym);
	responseType->setSynonymTable(synonymTable);

	return responseType;
}

bool APICallSuchThatClause::selectSynonymIsFoundInParam() {
	return (selectSynonym == suchThatClause.firstParameter || selectSynonym == suchThatClause.secondParameter);
}

bool APICallSuchThatClause::underscoreIsFoundInParam() {
	return (paramType.first == UNDERSCORE || paramType.second == UNDERSCORE);
}

bool APICallSuchThatClause::synonymIsStatementType(string synonymType) {
	return (synonymType == ASSIGNMENT_VAR || synonymType == STMT_VAR || synonymType == IF_VAR 
		|| synonymType == WHILE_VAR || synonymType == READ_VAR);
}

map<pair<string, string>, APICallSuchThatClause*> APICallSuchThatClause::buildModifiesUsesMap(SUCH_THAT_CLAUSE suchThatClause, 
	map<string, string> synonymTable) {
	map<pair<string, string>, APICallSuchThatClause*> modifiesUsesTable;

	modifiesUsesTable[make_pair(STMT_NO, VARIABLE)] = new BooleanResponse();
	modifiesUsesTable[make_pair(PROC_NAME, VARIABLE)] = new BooleanResponse();
	modifiesUsesTable[make_pair(STMT_NO, UNDERSCORE)] = new BooleanResponse();
	modifiesUsesTable[make_pair(PROC_NAME, UNDERSCORE)] = new BooleanResponse();

	modifiesUsesTable[make_pair(STMT_NO, SYNONYM)] = new StringVectorResponse();
	modifiesUsesTable[make_pair(PROC_NAME, SYNONYM)] = new StringVectorResponse();
	
	
	string synonymType = synonymTable[suchThatClause.firstParameter];
	if (synonymIsStatementType(synonymType)) {	// Statements Synonyms
		modifiesUsesTable[make_pair(SYNONYM, VARIABLE)] = new IntVectorResponse();
		modifiesUsesTable[make_pair(SYNONYM, SYNONYM)] = new IntStringPairVectorResponse();
		modifiesUsesTable[make_pair(SYNONYM, UNDERSCORE)] = new IntVectorResponse();
	}
	else {	// Procedure Synonyms
		modifiesUsesTable[make_pair(SYNONYM, VARIABLE)] = new StringVectorResponse();
		modifiesUsesTable[make_pair(SYNONYM, SYNONYM)] = new StringStringPairVectorResponse();
		modifiesUsesTable[make_pair(SYNONYM, UNDERSCORE)] = new StringVectorResponse();
	}

	return modifiesUsesTable;
}

map<pair<string, string>, APICallSuchThatClause*> APICallSuchThatClause::buildFollowsParentMap() {
	map<pair<string, string>, APICallSuchThatClause*> followsParentTable;

	followsParentTable[make_pair(STMT_NO, STMT_NO)] = new BooleanResponse();
	followsParentTable[make_pair(STMT_NO, UNDERSCORE)] = new BooleanResponse();
	followsParentTable[make_pair(UNDERSCORE, STMT_NO)] = new BooleanResponse();
	followsParentTable[make_pair(UNDERSCORE, UNDERSCORE)] = new BooleanResponse();

	followsParentTable[make_pair(SYNONYM, STMT_NO)] = new IntVectorResponse();
	followsParentTable[make_pair(STMT_NO, SYNONYM)] = new IntVectorResponse();
	followsParentTable[make_pair(UNDERSCORE, SYNONYM)] = new IntVectorResponse();
	followsParentTable[make_pair(SYNONYM, UNDERSCORE)] = new IntVectorResponse();

	followsParentTable[make_pair(SYNONYM, SYNONYM)] = new IntIntPairVectorResponse();

	return followsParentTable;
}

map<string, map<pair<string, string>, APICallSuchThatClause*>> APICallSuchThatClause::buildFunctionMap(SUCH_THAT_CLAUSE suchThatClause,
	map<string, string> synonymTable) {
	map<string, map<pair<string, string>, APICallSuchThatClause*>> functionMap;

	functionMap[USES_RS] = buildModifiesUsesMap(suchThatClause, synonymTable);
	functionMap[MODIFIES_RS] = buildModifiesUsesMap(suchThatClause, synonymTable);
	functionMap[FOLLOWS_RS] = buildFollowsParentMap();
	functionMap[PARENT_RS] = buildFollowsParentMap();

	return functionMap;
}