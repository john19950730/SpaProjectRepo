#pragma once
#include "APICallSuchThatClause.h"
#include "Result.h"
#include <vector>

class IntVectorResponse : public APICallSuchThatClause {
public:
	IntVectorResponse();
private:
	IntVectorResult* apiCallForFollows();
	IntVectorResult* apiCallForParent();
	IntVectorResult* apiCallForUses();
	IntVectorResult* apiCallForModifies();
};