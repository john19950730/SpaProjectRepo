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

	vector<int> getStmtsThatUsesVariable(vector<int> v, string variable);
};