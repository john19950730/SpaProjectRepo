#pragma once
#include "QueryObjStructures.h"
#include "APICall.h"
#include "Result.h"

#include <string>
#include <vector>

using namespace std;

class APICallPatternClause : public APICall {
public:
	APICallPatternClause(pair<string, string> paramType, PATTERN_CLAUSE patternClause,
		string selectSynonym, map<string, string> synonymTable);
	Result* executeApiCall();
private:
	PATTERN_CLAUSE patternClause;

	BooleanResult* getBooleanResponse();
	IntVectorResult* getIntVectorResponse();
	IntStringPairVectorResult* getIntStringVectorResponse();

	vector<string> selectResults(bool hasResults, vector<int> results);
	string intVectorToString(vector<int> input);
	vector<string> convertVectorIntToVectorStr(vector<int> input);
};