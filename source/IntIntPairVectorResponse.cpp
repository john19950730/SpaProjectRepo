#include "IntIntPairVectorResponse.h"
#include "PKB.h"

IntIntPairVectorResponse::IntIntPairVectorResponse() : APICallSuchThatClause() {}

vector<string> IntIntPairVectorResponse::apiCallForFollows() {
	vector< pair<int, int> > result;
	cout << "PKB::getAllFollowsPair(suchThatClause.hasTransitiveClosure)" << endl;
	//result = PKB::getAllFollowsPair(suchThatClause.hasTransitiveClosure);
	return getResult(result);
}

vector<string> IntIntPairVectorResponse::apiCallForParent() {
	vector< pair<int, int> > result;
	cout << "PKB::getAllParentPair(suchThatClause.hasTransitiveClosure)" << endl;
	//result = PKB::getAllParentPair(suchThatClause.hasTransitiveClosure);
	return getResult(result);
}

vector<string> IntIntPairVectorResponse::apiCallForUses() {
	return vector<string>();
}

vector<string> IntIntPairVectorResponse::apiCallForModifies() {
	return vector<string>();
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