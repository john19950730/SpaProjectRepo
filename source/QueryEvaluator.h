#pragma once
#include "Result.h"
#include "QueryObject.h"
#include <vector>

using namespace std;

class QueryEvaluator {
private:
	QueryObject *queryObject;
public:
	QueryEvaluator(QueryObject *queryObject);

	vector<string> evaluateQueryObject();
	Result* evaluateSuchThatClause();
	Result* evaluatePatternClause();
	
	vector<string> noCommonSynonym(Result* firstResult, Result* secondResult);

	vector<string> getResults(Result* result);
	vector<string> getResults(Result* firstResult, Result* secondResult);

	pair<string, string> getParamType(SUCH_THAT_CLAUSE clause);
	pair<string, string> getParamType(PATTERN_CLAUSE clause);

	vector<string> selectFrom(map < string, vector<string> > selectMap);
};