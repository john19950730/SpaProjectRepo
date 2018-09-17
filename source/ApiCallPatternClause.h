#pragma once
#include "QueryObjStructures.h"
#include <string>
#include <vector>

using namespace std;

class ApiCallPatternClause {
public:
	ApiCallPatternClause(pair<string, string> paramType, PATTERN_CLAUSE patternClause, string selectSynonym);
	string executeApiCall();
private:
	pair<string, string> paramType;
	PATTERN_CLAUSE patternClause;
	string selectSynonym;

	string selectResults(bool hasResults, vector<int> results);
};