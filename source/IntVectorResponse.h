#pragma once
#include "APICallResponse.h"
#include <vector>

class IntVectorResponse : public APICallResponse {
public:
	IntVectorResponse();
private:
	string apiCallForFollows();
	string apiCallForParent();
	string apiCallForUses();
	string apiCallForModifies();

	// Helper methods
	static string intVectorToString(vector<int> input);
	string getResults(vector<int> result);
};