#include "IntIntPairVectorResponse.h"
#include "PKB.h"

IntIntPairVectorResponse::IntIntPairVectorResponse() : APICallResponse() {}

string IntIntPairVectorResponse::apiCallForFollows() {
	vector< pair<int, int> > result;
	result = PKB::getAllFollowsPair(suchThatClause.hasTransitiveClosure);
	return getResult(result);
}

string IntIntPairVectorResponse::apiCallForParent() {
	vector< pair<int, int> > result;
	result = PKB::getAllParentPair(suchThatClause.hasTransitiveClosure);
	return getResult(result);
}

string IntIntPairVectorResponse::apiCallForUses() {
	return "";
}

string IntIntPairVectorResponse::apiCallForModifies() {
	return "";
}

string IntIntPairVectorResponse::getResult(vector<pair<int, int>> result) {
	if (result.empty()) return getNoResults();
	if (!selectSynonymIsFoundInParam()) return getImmediateResults();
	return extractedResults(result);
}

string IntIntPairVectorResponse::extractedResults(vector<pair<int, int>> result) {
	string extractedResult = selectSynonym == suchThatClause.firstParameter 
		? extractFirstParam(result) : extractSecondParam(result);
	return extractedResult;
}

string IntIntPairVectorResponse::extractFirstParam(vector<pair<int, int>> input) {
	string s = "";
	for (pair<int, int> i : input) {
		s += " " + to_string(i.first);
	}
	return s;
}

string IntIntPairVectorResponse::extractSecondParam(vector<pair<int, int>> input) {
	string s = "";
	for (pair<int, int> i : input) {
		s += " " + to_string(i.second);
	}
	return s;
}