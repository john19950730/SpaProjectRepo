#pragma once
#include "APICallResponse.h"
#include <vector>

class IntVectorResponse : public APICallResponse {
public:
	IntVectorResponse();
	IntVectorResponse(string typeOfRs, pair<string, string> paramType, SUCH_THAT_CLAUSE suchThatClause,
		string selectSynonym, map<string, string> synonymTable);
private:
	string apiCallForFollows();
	string apiCallForParent();
	string apiCallForUses();
	string apiCallForModifies();

	// Helper methods
	static string intVectorToString(vector<int> input);
	string getResults(vector<int> result);
};