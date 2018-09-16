#include "StringStringPairVectorResponse.h"
#include "PKB.h"

StringStringPairVectorResponse::StringStringPairVectorResponse() : APICallResponse() {}

string StringStringPairVectorResponse::apiCallForFollows() {
	return "";
}
string StringStringPairVectorResponse::apiCallForParent() {
	return "";
}
string StringStringPairVectorResponse::apiCallForUses() {
	vector< pair<string, string> > result;
	result = PKB::getAllProcedureUsesVariablePairs();
	return getResult(result);
}
string StringStringPairVectorResponse::apiCallForModifies() {
	vector< pair<string, string> > result;
	result = PKB::getAllProcedureModifiesVariablePairs();
	return getResult(result);
}

string StringStringPairVectorResponse::getResult(vector<pair<string, string>> result) {
	if (result.empty()) return getNoResults();
	if (!selectSynonymIsFoundInParam()) return getImmediateResults();
	return extractedResults(result);
}

string StringStringPairVectorResponse::extractedResults(vector<pair<string, string>> result) {
	string extractedResult = selectSynonym == suchThatClause.firstParameter
		? extractFirstParam(result) : extractSecondParam(result);
	return extractedResult;
}

string StringStringPairVectorResponse::extractFirstParam(vector < pair<string, string> > input) {
	string s = "";
	for (pair<string, string> i : input) {
		s += " " + i.first;
	}
	return s;
}

string StringStringPairVectorResponse::extractSecondParam(vector < pair<string, string> > input) {
	string s = "";
	for (pair<string, string> i : input) {
		s += " " + i.second;
	}
	return s;
}