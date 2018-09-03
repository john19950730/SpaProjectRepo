#pragma once
#include "QueryTree.h"

using namespace std;

class QueryEvaluator {
private:
public:
	static string evaluateQueryTree(QueryTree *queryTree);
};