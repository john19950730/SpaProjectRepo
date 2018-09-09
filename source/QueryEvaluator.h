#pragma once
#include "QueryObject.h"

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
};