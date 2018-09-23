#pragma once
#include "QueryObject.h"
#include <vector>

using namespace std;

class QueryEvaluator {
private:
	QueryObject *queryObject;
public:
	QueryEvaluator(QueryObject *queryObject);

	vector<string> evaluateQueryObject();
	vector<string> evaluateSuchThatClause();
	vector<string> evaluatePatternClause();
	vector<string> evaluateSuchThatAndPatternClause();
	
	pair<string, string> getParamType(SUCH_THAT_CLAUSE clause);
	pair<string, string> getParamType(PATTERN_CLAUSE clause);
};