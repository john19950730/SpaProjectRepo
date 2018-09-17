#include "StringStringPairVectorResponse.h"
#include "PKB.h"

StringStringPairVectorResponse::StringStringPairVectorResponse() : APICallSuchThatClause() {}

vector<string> StringStringPairVectorResponse::apiCallForFollows() {
	return vector<string>();
}

vector<string> StringStringPairVectorResponse::apiCallForParent() {
	return vector<string>();
}

vector<string> StringStringPairVectorResponse::apiCallForUses() {
	vector< pair<string, string> > result;
	cout << "PKB::getAllProcedureUsesVariablePairs()" << endl;
	//result = PKB::getAllProcedureUsesVariablePairs();
	return getResult(result);
}

vector<string> StringStringPairVectorResponse::apiCallForModifies() {
	vector< pair<string, string> > result;
	cout << "PKB::getAllProcedureModifiesVariablePairs()" << endl;
	//result = PKB::getAllProcedureModifiesVariablePairs();
	return getResult(result);
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