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

	IntVectorResult* getIntVectorResponse();
	IntStringPairVectorResult* getIntStringVectorResponse();
};