#pragma once
#include "QueryObject.h"
#include <vector>

using namespace std;

class QueryEvaluator {
private:
	QueryObject *queryObject;
public:
	QueryEvaluator(QueryObject *queryObject);

	string evaluateQueryObject();
	string evaluateSingleClause();
	string selectImmediateResults();
	string evaluateUsesClause();
	string evaluateModifiesClause();
	string evaluateFollowsClause();
	string evaluateParentClause();

	pair<string, string> getParamType(SUCH_THAT_CLAUSE clause);
	string selectIntermediateResult(vector<string> result, SUCH_THAT_CLAUSE clause);
	string noResult();
};