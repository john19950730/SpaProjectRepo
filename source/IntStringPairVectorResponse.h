#pragma once
#include "APICallSuchThatClause.h"
#include "Result.h"
#include <vector>

class IntStringPairVectorResponse : public APICallSuchThatClause {
public:
	IntStringPairVectorResponse();
private:
	IntStringPairVectorResult* apiCallForFollows();
	IntStringPairVectorResult* apiCallForParent();
	IntStringPairVectorResult* apiCallForUses();
	IntStringPairVectorResult* apiCallForModifies();
};