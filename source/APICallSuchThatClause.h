#pragma once
#include "APICall.h"
#include "QueryObjStructures.h"
#include <string>
#include <map>

using namespace std;

// Abstract class
class APICallSuchThatClause : public APICall {
public:
	vector<string> executeApiCall();
	static APICallSuchThatClause* getApiCallResponse(string typeOfRs, pair<string, string> paramType,
		SUCH_THAT_CLAUSE suchThatClause, string selectSynonym, map<string, string> synonymTable);
protected:
	// Attributes
	string typeOfRs;
	SUCH_THAT_CLAUSE suchThatClause;

	// Constructor
	APICallSuchThatClause();

	// Setter methods
	void setTypeOfRs(string typeOfRs);
	void setSuchThatClause(SUCH_THAT_CLAUSE suchThatClause);

	// Abstracted methods without implementation
	virtual vector<string> apiCallForFollows() = 0;
	virtual vector<string> apiCallForParent() = 0;
	virtual vector<string> apiCallForUses() = 0;
	virtual vector<string> apiCallForModifies() = 0;

	// Helper methods
	bool selectSynonymIsFoundInParam();
	bool underscoreIsFoundInParam();
	static bool synonymIsStatementType(string synonymType);

	// Map making
	static map<pair<string, string>, APICallSuchThatClause*> buildModifiesUsesMap(SUCH_THAT_CLAUSE suchThatClause, map<string, string> synonymTable);
	static map<pair<string, string>, APICallSuchThatClause*> buildFollowsParentMap();
	static map<string, map<pair<string, string>, APICallSuchThatClause*>> buildFunctionMap(SUCH_THAT_CLAUSE suchThatClause, map<string, string> synonymTable);
};