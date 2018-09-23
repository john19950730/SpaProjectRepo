#pragma once
#include "APICallSuchThatClause.h"
#include "Result.h"
#include <vector>

class IntIntPairVectorResponse : public APICallSuchThatClause {
public:
	IntIntPairVectorResponse();
private:
	IntIntPairVectorResult* apiCallForFollows();
	IntIntPairVectorResult* apiCallForParent();
	IntIntPairVectorResult* apiCallForUses();
	IntIntPairVectorResult* apiCallForModifies();
};