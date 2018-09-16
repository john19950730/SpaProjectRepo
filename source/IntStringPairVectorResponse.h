#pragma once
#include "APICallResponse.h"
#include <vector>

class IntStringPairVectorResponse : public APICallResponse {
public:
	IntStringPairVectorResponse();
private:
	string apiCallForFollows();
	string apiCallForParent();
	string apiCallForUses();
	string apiCallForModifies();

	string getResult(vector<pair<int, string>> result);

	string extractFirstParam(vector<pair<int, string>> input);
	string extractSecondParam(vector<pair<int, string>> input);
	string extractedResults(vector<pair<int, string>> result);
};