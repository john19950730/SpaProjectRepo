#pragma once
#include "APICallSuchThatClause.h"
#include <vector>

class IntStringPairVectorResponse : public APICallSuchThatClause {
public:
	IntStringPairVectorResponse();
private:
	vector<string> apiCallForFollows();
	vector<string> apiCallForParent();
	vector<string> apiCallForUses();
	vector<string> apiCallForModifies();

	vector<string> getResult(vector<pair<int, string>> result);

	vector<string> extractFirstParam(vector<pair<int, string>> input);
	vector<string> extractSecondParam(vector<pair<int, string>> input);
	vector<string> extractedResults(vector<pair<int, string>> result);
};