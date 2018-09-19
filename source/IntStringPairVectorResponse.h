#pragma once
#include "APICallSuchThatClause.h"
#include "Result.h"
#include <vector>

class IntStringPairVectorResponse : public APICallSuchThatClause {
public:
	IntStringPairVectorResponse();
private:
	IntStringPairVectorResult* apiCallForFollows();
	IntStringPairVectorResult* apiCallForParent();
	IntStringPairVectorResult* apiCallForUses();
	IntStringPairVectorResult* apiCallForModifies();

	vector<string> getResult(vector<pair<int, string>> result);

	vector<string> extractFirstParam(vector<pair<int, string>> input);
	vector<string> extractSecondParam(vector<pair<int, string>> input);
	vector<string> extractedResults(vector<pair<int, string>> result);
};