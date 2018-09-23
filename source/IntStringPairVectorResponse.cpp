#include "IntStringPairVectorResponse.h"
#include "PKB.h"
#include "Keywords.h"

using namespace keywords::clauseParamType;
using namespace keywords::query;

IntStringPairVectorResponse::IntStringPairVectorResponse() : APICallSuchThatClause() {}

IntStringPairVectorResult* IntStringPairVectorResponse::apiCallForFollows() {
	return NULL;
}

IntStringPairVectorResult* IntStringPairVectorResponse::apiCallForParent() {
	return NULL;
}

IntStringPairVectorResult* IntStringPairVectorResponse::apiCallForUses() {
	vector< pair<unsigned int, string> > result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	// First synonym is of statement type - second param is definitely variable synonym type
		
	result = PKB::getAllStmtUsesVariablePairs(synonymTable[firstParam]); // Uses(a, v)
	cout << "PKB::getAllStmtUsesVariablePairs(synonymTable[firstParam]); // Uses(a, v)" << endl;

	IntStringPairVectorResult* intStrPairResult = 
		new IntStringPairVectorResult(result, make_pair(firstParam, secondParam));

	return intStrPairResult;
}

IntStringPairVectorResult* IntStringPairVectorResponse::apiCallForModifies() {
	vector< pair<unsigned int, string> > result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	
	// First synonym is of statement type - second param is definitely variable synonym type
	
	result = PKB::getAllStmtModifiesVariablePairs(synonymTable[firstParam]); // Modifies(a, v)
	cout << "PKB::getAllStmtModifiesVariablePairs(synonymTable[firstParam]); // Modifies(a, v)" << endl;

	IntStringPairVectorResult* intStrPairResult =
		new IntStringPairVectorResult(result, make_pair(firstParam, secondParam));

	return intStrPairResult;
}