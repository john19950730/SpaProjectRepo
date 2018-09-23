#pragma once

#include <string>
using namespace std;

typedef struct SUCH_THAT_CLAUSE {
	string firstParameter;
	string secondParameter;
	bool hasTransitiveClosure;
	bool firstParamIsSynonym;
	bool secondParamIsSynonym;
} SUCH_THAT_CLAUSE;

typedef struct PATTERN_CLAUSE {
	string synonym;
	string firstParam;
	string secondParam;
	bool secondParamIsPartialExpr;
	bool firstParamIsSynonym;
} PATTERN_CLAUSE;