#pragma once
#include "APICallResponse.h"
#include "QueryObjStructures.h"

class BooleanResponse : public APICallResponse {
public:
	BooleanResponse();
	BooleanResponse(string typeOfRs, pair<string, string> paramType, SUCH_THAT_CLAUSE suchThatClause,
		string selectSynonym, map<string, string> synonymTable);
private:
	string apiCallForFollows();
	string apiCallForParent();
	string apiCallForUses();
	string apiCallForModifies();
};