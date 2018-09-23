#include "IntIntPairVectorResponse.h"
#include "PKB.h"

IntIntPairVectorResponse::IntIntPairVectorResponse() : APICallSuchThatClause() {}

IntIntPairVectorResult* IntIntPairVectorResponse::apiCallForFollows() {
	vector< pair<unsigned int, unsigned int> > result;
	string firstParamSyn = synonymTable[suchThatClause.firstParameter];
	string secondParamSyn = synonymTable[suchThatClause.secondParameter];

	result = PKB::getAllFollowsPair(firstParamSyn, secondParamSyn, suchThatClause.hasTransitiveClosure); // Follows(a, b)
	cout << "PKB::getAllFollowsPair(firstParamSyn, secondParamSyn, suchThatClause.hasTransitiveClosure); // Follows(a, b)" << endl;

	// e.g. Follows(s1,s1) - always false
	if (suchThatClause.firstParameter == suchThatClause.secondParameter) {
		result = {};
		cout << "Same Syonym: Follows(s1,s1)" << endl;
	}

	IntIntPairVectorResult* intIntPairVectorResult 
		= new IntIntPairVectorResult(result, make_pair(suchThatClause.firstParameter, suchThatClause.secondParameter));
	
	return intIntPairVectorResult;
}

IntIntPairVectorResult* IntIntPairVectorResponse::apiCallForParent() {
	vector< pair<unsigned int, unsigned int> > result;
	string firstParamSyn = synonymTable[suchThatClause.firstParameter];
	string secondParamSyn = synonymTable[suchThatClause.secondParameter];

	result = PKB::getAllParentPair(firstParamSyn, secondParamSyn, suchThatClause.hasTransitiveClosure); // Parent(a, b)
	cout << "PKB::getAllParentPair(firstParamSyn, secondParamSyn, suchThatClause.hasTransitiveClosure); // Parent(a, b)" << endl;
	
	// e.g. Parent(s1,s1) - always false
	if (suchThatClause.firstParameter == suchThatClause.secondParameter) {
		result = {};
		cout << "Same Syonym: Parent(s1,s1)" << endl;
	}

	IntIntPairVectorResult* intIntPairVectorResult
		= new IntIntPairVectorResult(result, make_pair(suchThatClause.firstParameter, suchThatClause.secondParameter));

	return intIntPairVectorResult;
}

IntIntPairVectorResult* IntIntPairVectorResponse::apiCallForUses() {
	return NULL;
}

IntIntPairVectorResult* IntIntPairVectorResponse::apiCallForModifies() {
	return NULL;
}