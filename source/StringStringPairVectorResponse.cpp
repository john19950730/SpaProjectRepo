#include "StringStringPairVectorResponse.h"
#include "PKB.h"
#include "Keywords.h"

StringStringPairVectorResponse::StringStringPairVectorResponse() : APICallSuchThatClause() {}

vector<string> StringStringPairVectorResponse::apiCallForFollows() {
	return vector<string>();
}

vector<string> StringStringPairVectorResponse::apiCallForParent() {
	return vector<string>();
}

vector<string> StringStringPairVectorResponse::apiCallForUses() {
	vector< pair<string, string> > result;
	vector<string> results;

	//result = PKB::getAllProcedureUsesVariablePairs(); // Uses(p, v)
	results.push_back("PKB::getAllProcedureUsesVariablePairs(); // Uses(p, v)");

	return results;
}

vector<string> StringStringPairVectorResponse::apiCallForModifies() {
	vector< pair<string, string> > result;
	vector<string> results;

	//result = PKB::getAllProcedureModifiesVariablePairs(); // Modifies(p, v)
	results.push_back("PKB::getAllProcedureModifiesVariablePairs(); // Modifies(p, v)");

	return results;
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