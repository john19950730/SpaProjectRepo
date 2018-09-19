#pragma once
#include "APICallSuchThatClause.h"
#include "Result.h"
#include <vector>

class IntIntPairVectorResponse : public APICallSuchThatClause {
public:
	IntIntPairVectorResponse();
private:
	IntIntPairVectorResult* apiCallForFollows();
	IntIntPairVectorResult* apiCallForParent();
	IntIntPairVectorResult* apiCallForUses();
	IntIntPairVectorResult* apiCallForModifies();

	vector<string> getResult(vector<pair<int, int>> result);

	vector<string> extractFirstParam(vector<pair<int, int>> input);
	vector<string> extractSecondParam(vector<pair<int, int>> input);
	vector<string> extractedResults(vector<pair<int, int>> result);
};