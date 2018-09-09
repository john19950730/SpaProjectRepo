#pragma once
#include "QueryObject.h"

using namespace std;

class QueryEvaluator {
private:
	QueryObject *queryObject;
public:
	QueryEvaluator(QueryObject *queryObject);

	string evaluateQueryObject();
	string selectImmediateResults();
	string evaluateUsesClause();
	string evaluateModifiesClause();
	string evaluateFollowsClause();
	string evaluateParentClause();

	bool isInteger(string str);	// to be moved to utility class	
};