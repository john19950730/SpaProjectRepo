#pragma once
#include "APICallSuchThatClause.h"
#include <vector>

class IntIntPairVectorResponse : public APICallSuchThatClause {
public:
	IntIntPairVectorResponse();
private:
	vector<string> apiCallForFollows();
	vector<string> apiCallForParent();
	vector<string> apiCallForUses();
	vector<string> apiCallForModifies();

	vector<string> getResult(vector<pair<int, int>> result);

	vector<string> extractFirstParam(vector<pair<int, int>> input);
	vector<string> extractSecondParam(vector<pair<int, int>> input);
	vector<string> extractedResults(vector<pair<int, int>> result);
};