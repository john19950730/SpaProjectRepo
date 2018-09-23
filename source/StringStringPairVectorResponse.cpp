#include "StringStringPairVectorResponse.h"
#include "PKB.h"
#include "Keywords.h"

StringStringPairVectorResponse::StringStringPairVectorResponse() : APICallSuchThatClause() {}

StringStringPairVectorResult* StringStringPairVectorResponse::apiCallForFollows() {
	return NULL;
}

StringStringPairVectorResult* StringStringPairVectorResponse::apiCallForParent() {
	return NULL;
}

StringStringPairVectorResult* StringStringPairVectorResponse::apiCallForUses() {
	vector< pair<string, string> > result;

	result = PKB::getAllProcedureUsesVariablePairs(); // Uses(p, v)
	cout << "PKB::getAllProcedureUsesVariablePairs(); // Uses(p, v)" << endl;

	StringStringPairVectorResult *strStrResult = new StringStringPairVectorResult(result,
		make_pair(suchThatClause.firstParameter, suchThatClause.secondParameter));
	return strStrResult;
}

StringStringPairVectorResult* StringStringPairVectorResponse::apiCallForModifies() {
	vector< pair<string, string> > result;

	result = PKB::getAllProcedureModifiesVariablePairs(); // Modifies(p, v)
	cout << "PKB::getAllProcedureModifiesVariablePairs(); // Modifies(p, v)" << endl;

	StringStringPairVectorResult *strStrResult = new StringStringPairVectorResult(result,
		make_pair(suchThatClause.firstParameter, suchThatClause.secondParameter));
	return strStrResult;
}