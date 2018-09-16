#pragma once
#include "QueryObjStructures.h"
#include <string>
#include <map>

using namespace std;

// Abstract class
class APICallResponse {
public:
	string executeApiCall();
	static APICallResponse* getApiCallResponse(string typeOfRs, pair<string, string> paramType,
		SUCH_THAT_CLAUSE suchThatClause, string selectSynonym, map<string, string> synonymTable);

// Virtual methods without implementation - Derived classes to implement this
protected:
	string typeOfRs;
	pair<string, string> paramType;
	SUCH_THAT_CLAUSE suchThatClause;
	string selectSynonym;
	map<string, string> synonymTable;

	APICallResponse();
	APICallResponse(string typeOfRs, pair<string, string> paramType, SUCH_THAT_CLAUSE suchThatClause, 
		string selectSynonym, map<string, string> synonymTable);

	// Setter methods
	void setTypeOfRs(string typeOfRs);
	void setParamType(pair<string, string> paramType);
	void setSuchThatClause(SUCH_THAT_CLAUSE suchThatClause);
	void setSelectSynonym(string selectSynonym);
	void setSynonymTable(map<string, string> synonymTable);

	// Generic method
	string getImmediateResults();
	string getNoResults();
	
	// Abstracted methods without implementation
	virtual string apiCallForFollows() = 0;
	virtual string apiCallForParent() = 0;
	virtual string apiCallForUses() = 0;
	virtual string apiCallForModifies() = 0;

	// Helper methods
	bool selectSynonymIsFoundInParam();
	bool underscoreIsFoundInParam();
	static bool synonymIsStatementType(string synonymType);

	// Map making
	static map<pair<string, string>, APICallResponse*> buildModifiesUsesMap(SUCH_THAT_CLAUSE suchThatClause, map<string, string> synonymTable);
	static map<pair<string, string>, APICallResponse*> buildFollowsParentMap();
	static map<string, map<pair<string, string>, APICallResponse*>> buildFunctionMap(SUCH_THAT_CLAUSE suchThatClause, map<string, string> synonymTable);

};