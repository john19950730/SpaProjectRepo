#pragma once
#include "APICallSuchThatClause.h"
#include "Result.h"
#include <vector>

class StringStringPairVectorResponse : public APICallSuchThatClause {
public:
	StringStringPairVectorResponse();
private:
	StringStringPairVectorResult* apiCallForFollows();
	StringStringPairVectorResult* apiCallForParent();
	StringStringPairVectorResult* apiCallForUses();
	StringStringPairVectorResult* apiCallForModifies();
};