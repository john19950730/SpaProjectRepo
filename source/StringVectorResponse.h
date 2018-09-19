#pragma once
#include "APICallSuchThatClause.h"
#include <vector>

class StringVectorResponse : public APICallSuchThatClause {
public:
	StringVectorResponse();
private:
	StringVectorResult* apiCallForFollows();
	StringVectorResult* apiCallForParent();
	StringVectorResult* apiCallForUses();
	StringVectorResult* apiCallForModifies();

	string strVectorToString(vector<string> input);
	vector<string> getResults(vector<string> result);
};