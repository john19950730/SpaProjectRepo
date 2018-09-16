#pragma once
#include "APICallResponse.h"
#include <vector>

class StringStringPairVectorResponse : public APICallResponse {
public:
	StringStringPairVectorResponse();
private:
	string apiCallForFollows();
	string apiCallForParent();
	string apiCallForUses();
	string apiCallForModifies();

	string getResult(vector<pair<string, string>> result);

	string extractedResults(vector<pair<string, string>> result);
	string extractFirstParam(vector < pair<string, string> > input);
	string extractSecondParam(vector < pair<string, string> > input);
};