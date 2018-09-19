#include "IntIntPairVectorResponse.h"
#include "PKB.h"

IntIntPairVectorResponse::IntIntPairVectorResponse() : APICallSuchThatClause() {}

IntIntPairVectorResult* IntIntPairVectorResponse::apiCallForFollows() {
	vector< pair<unsigned int, unsigned int> > result;
	string firstParamSyn = synonymTable[suchThatClause.firstParameter];
	string secondParamSyn = synonymTable[suchThatClause.secondParameter];
	vector<string> results;

	result = PKB::getAllFollowsPair(firstParamSyn, secondParamSyn, suchThatClause.hasTransitiveClosure); // Follows(a, b)
	cout << "PKB::getAllFollowsPair(firstParamSyn, secondParamSyn, suchThatClause.hasTransitiveClosure); // Follows(a, b)" << endl;

	IntIntPairVectorResult* intIntPairVectorResult 
		= new IntIntPairVectorResult(result, make_pair(suchThatClause.firstParameter, suchThatClause.secondParameter));
	
	return intIntPairVectorResult;
}

IntIntPairVectorResult* IntIntPairVectorResponse::apiCallForParent() {
	vector< pair<unsigned int, unsigned int> > result;
	string firstParamSyn = synonymTable[suchThatClause.firstParameter];
	string secondParamSyn = synonymTable[suchThatClause.secondParameter];
	vector<string> results;

	result = PKB::getAllParentPair(firstParamSyn, secondParamSyn, suchThatClause.hasTransitiveClosure); // Parent(a, b)
	cout << "PKB::getAllParentPair(firstParamSyn, secondParamSyn, suchThatClause.hasTransitiveClosure); // Parent(a, b)" << endl;
	
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

vector<string> IntIntPairVectorResponse::getResult(vector<pair<int, int>> result) {
	if (result.empty()) return getNoResults();
	if (!selectSynonymIsFoundInParam()) return getImmediateResults();
	return extractedResults(result);
}

vector<string> IntIntPairVectorResponse::extractedResults(vector<pair<int, int>> result) {
	vector<string> extractedResult = selectSynonym == suchThatClause.firstParameter
		? extractFirstParam(result) : extractSecondParam(result);
	return extractedResult;
}

vector<string> IntIntPairVectorResponse::extractFirstParam(vector<pair<int, int>> input) {
	vector<string> strVector;
	for (pair<int, int> i : input) {
		strVector.push_back(to_string(i.first));
	}
	return strVector;
}

vector<string> IntIntPairVectorResponse::extractSecondParam(vector<pair<int, int>> input) {
	vector<string> strVector;
	for (pair<int, int> i : input) {
		strVector.push_back(to_string(i.second));
	}
	return strVector;
}