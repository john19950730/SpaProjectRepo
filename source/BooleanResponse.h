#pragma once
#include "APICallSuchThatClause.h"
#include "QueryObjStructures.h"
#include "Result.h"

class BooleanResponse : public APICallSuchThatClause {
public:
	BooleanResponse();
private:
	BooleanResult* apiCallForFollows();
	BooleanResult* apiCallForParent();
	BooleanResult* apiCallForUses();
	BooleanResult* apiCallForModifies();
};