#pragma once
#include "QueryObjStructures.h"
#include "APICall.h"

#include <string>
#include <vector>

using namespace std;

class APICallPatternClause : public APICall {
public:
	APICallPatternClause(pair<string, string> paramType, PATTERN_CLAUSE patternClause,
		string selectSynonym, map<string, string> synonymTable);
	vector<string> executeApiCall();
private:
	PATTERN_CLAUSE patternClause;

	vector<string> selectResults(bool hasResults, vector<int> results);
	string intVectorToString(vector<int> input);
	vector<string> convertVectorIntToVectorStr(vector<int> input);
};