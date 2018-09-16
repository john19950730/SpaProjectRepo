#include "IntStringPairVectorResponse.h"
#include "PKB.h"
#include "Keywords.h"

using namespace keywords::query;

IntStringPairVectorResponse::IntStringPairVectorResponse() : APICallResponse() {}

string IntStringPairVectorResponse::apiCallForFollows() {
	return "";
}
string IntStringPairVectorResponse::apiCallForParent() {
	return "";
}
string IntStringPairVectorResponse::apiCallForUses() {
	vector< pair<int, string> > result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	if (synonymTable[firstParam] == ASSIGNMENT_VAR) {
		return "PKB::getAllAssignmentUsesVariablePairs()";
		result = PKB::getAllAssignmentUsesVariablePairs();
	}
	else if (synonymTable[firstParam] == STMT_VAR) {
		return "PKB::getAllStmtUsesVariablePairs()";
		result = PKB::getAllStmtUsesVariablePairs();
	}
	return getResult(result);
}
string IntStringPairVectorResponse::apiCallForModifies() {
	vector< pair<int, string> > result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	if (synonymTable[firstParam] == ASSIGNMENT_VAR) {
		return "PKB::getAllAssignmentModifiesVariablePairs()";
		result = PKB::getAllAssignmentModifiesVariablePairs();
	}
	else if (synonymTable[firstParam] == STMT_VAR) {
		return "PKB::getAllStmtModifiesVariablePairs()";
		result = PKB::getAllStmtModifiesVariablePairs();
	}
	return getResult(result);
}

string IntStringPairVectorResponse::getResult(vector<pair<int, string>> result) {
	if (result.empty()) return getNoResults();
	if (!selectSynonymIsFoundInParam()) return getImmediateResults();
	return extractedResults(result);
}

string IntStringPairVectorResponse::extractedResults(vector<pair<int, string>> result) {
	string extractedResult = selectSynonym == suchThatClause.firstParameter
		? extractFirstParam(result) : extractSecondParam(result);
	return extractedResult;
}

string IntStringPairVectorResponse::extractFirstParam(vector<pair<int, string>> input) {
	string s = "";
	for (pair<int, string> i : input) {
		s += " " + to_string(i.first);
	}
	return s;
}

string IntStringPairVectorResponse::extractSecondParam(vector<pair<int, string>> input) {
	string s = "";
	for (pair<int, string> i : input) {
		s += " " + i.second;
	}
	return s;
}