#pragma once
#include "APICallSuchThatClause.h"
#include "Result.h"
#include <vector>

class IntVectorResponse : public APICallSuchThatClause {
public:
	IntVectorResponse();
private:
	IntVectorResult* apiCallForFollows();
	IntVectorResult* apiCallForParent();
	IntVectorResult* apiCallForUses();
	IntVectorResult* apiCallForModifies();

	// Helper methods
	static string intVectorToString(vector<int> input);
	static vector<string> convertVectorIntToVectorStr(vector<int> input);
	vector<string> getResults(vector<int> result);
};