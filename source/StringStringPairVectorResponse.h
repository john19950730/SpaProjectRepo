#pragma once
#include "APICallSuchThatClause.h"
#include "Result.h"
#include <vector>

class StringStringPairVectorResponse : public APICallSuchThatClause {
public:
	StringStringPairVectorResponse();
private:
	StringStringPairVectorResult* apiCallForFollows();
	StringStringPairVectorResult* apiCallForParent();
	StringStringPairVectorResult* apiCallForUses();
	StringStringPairVectorResult* apiCallForModifies();

	vector<string> getResult(vector<pair<string, string>> result);

	vector<string> extractedResults(vector<pair<string, string>> result);
	vector<string> extractFirstParam(vector < pair<string, string> > input);
	vector<string> extractSecondParam(vector < pair<string, string> > input);
};