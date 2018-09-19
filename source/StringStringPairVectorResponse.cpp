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
	vector<string> results;

	result = PKB::getAllProcedureUsesVariablePairs(); // Uses(p, v)
	cout << "PKB::getAllProcedureUsesVariablePairs(); // Uses(p, v)" << endl;

	StringStringPairVectorResult *strStrResult = new StringStringPairVectorResult(result,
		make_pair(suchThatClause.firstParameter, suchThatClause.secondParameter));
	return strStrResult;
}

StringStringPairVectorResult* StringStringPairVectorResponse::apiCallForModifies() {
	vector< pair<string, string> > result;
	vector<string> results;

	result = PKB::getAllProcedureModifiesVariablePairs(); // Modifies(p, v)
	cout << "PKB::getAllProcedureModifiesVariablePairs(); // Modifies(p, v)" << endl;

	StringStringPairVectorResult *strStrResult = new StringStringPairVectorResult(result,
		make_pair(suchThatClause.firstParameter, suchThatClause.secondParameter));
	return strStrResult;
}

vector<string> StringStringPairVectorResponse::getResult(vector<pair<string, string>> result) {
	if (result.empty()) return getNoResults();
	if (!selectSynonymIsFoundInParam()) return getImmediateResults();
	return extractedResults(result);
}

vector<string> StringStringPairVectorResponse::extractedResults(vector<pair<string, string>> result) {
	vector<string> extractedResult = selectSynonym == suchThatClause.firstParameter
		? extractFirstParam(result) : extractSecondParam(result);
	return extractedResult;
}

vector<string> StringStringPairVectorResponse::extractFirstParam(vector < pair<string, string> > input) {
	vector<string> strVector;
	for (pair<string, string> i : input) {
		strVector.push_back(i.first);
	}
	return strVector;
}

vector<string> StringStringPairVectorResponse::extractSecondParam(vector < pair<string, string> > input) {
	vector<string> strVector;
	for (pair<string, string> i : input) {
		strVector.push_back(i.second);
	}
	return strVector;
}