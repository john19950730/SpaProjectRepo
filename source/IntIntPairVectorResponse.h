#pragma once
#include "APICallResponse.h"
#include <vector>

class IntIntPairVectorResponse : public APICallResponse {
public:
	IntIntPairVectorResponse();
private:
	string apiCallForFollows();
	string apiCallForParent();
	string apiCallForUses();
	string apiCallForModifies();

	string getResult(vector<pair<int, int>> result);

	string extractFirstParam(vector<pair<int, int>> input);
	string extractSecondParam(vector<pair<int, int>> input);
	string extractedResults(vector<pair<int, int>> result);
};