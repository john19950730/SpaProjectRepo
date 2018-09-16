#pragma once
#include "APICallResponse.h"
#include "QueryObjStructures.h"

class BooleanResponse : public APICallResponse {
public:
	BooleanResponse();
private:
	string apiCallForFollows();
	string apiCallForParent();
	string apiCallForUses();
	string apiCallForModifies();
};