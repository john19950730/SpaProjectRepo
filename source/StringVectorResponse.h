#pragma once
#include "APICallSuchThatClause.h"
#include <vector>

class StringVectorResponse : public APICallSuchThatClause {
public:
	StringVectorResponse();
private:
	vector<string> apiCallForFollows();
	vector<string> apiCallForParent();
	vector<string> apiCallForUses();
	vector<string> apiCallForModifies();

	string strVectorToString(vector<string> input);
	vector<string> getResults(vector<string> result);
};