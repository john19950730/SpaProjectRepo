#pragma once
#include "APICallSuchThatClause.h"
#include <vector>

class StringStringPairVectorResponse : public APICallSuchThatClause {
public:
	StringStringPairVectorResponse();
private:
	vector<string> apiCallForFollows();
	vector<string> apiCallForParent();
	vector<string> apiCallForUses();
	vector<string> apiCallForModifies();

	vector<string> getResult(vector<pair<string, string>> result);

	vector<string> extractedResults(vector<pair<string, string>> result);
	vector<string> extractFirstParam(vector < pair<string, string> > input);
	vector<string> extractSecondParam(vector < pair<string, string> > input);
};