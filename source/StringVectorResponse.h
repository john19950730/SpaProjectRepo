#pragma once
#include "APICallResponse.h"
#include <vector>

class StringVectorResponse : public APICallResponse {
public:
	StringVectorResponse();
private:
	string apiCallForFollows();
	string apiCallForParent();
	string apiCallForUses();
	string apiCallForModifies();

	string strVectorToString(vector<string> input);
	string getResults(vector<string> result);
};