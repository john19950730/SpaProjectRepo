#pragma once
#include "APICallSuchThatClause.h"
#include "QueryObjStructures.h"

class BooleanResponse : public APICallSuchThatClause {
public:
	BooleanResponse();
private:
	vector<string> apiCallForFollows();
	vector<string> apiCallForParent();
	vector<string> apiCallForUses();
	vector<string> apiCallForModifies();
};