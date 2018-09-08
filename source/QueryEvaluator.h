#pragma once
#include "QueryObject.h"

using namespace std;

class QueryEvaluator {
private:
public:
	static string evaluateQueryObject(QueryObject *queryObject);
};