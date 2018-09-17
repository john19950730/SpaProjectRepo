#pragma once
#include "APICallSuchThatClause.h"
#include <vector>

class IntVectorResponse : public APICallSuchThatClause {
public:
	IntVectorResponse();
private:
	vector<string> apiCallForFollows();
	vector<string> apiCallForParent();
	vector<string> apiCallForUses();
	vector<string> apiCallForModifies();

	// Helper methods
	static string intVectorToString(vector<int> input);
	static vector<string> convertVectorIntToVectorStr(vector<int> input);
	vector<string> getResults(vector<int> result);
};