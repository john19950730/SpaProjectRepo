#include "IntStringPairVectorResponse.h"
#include "PKB.h"
#include "Keywords.h"

using namespace keywords::query;

IntStringPairVectorResponse::IntStringPairVectorResponse() : APICallSuchThatClause() {}

vector<string> IntStringPairVectorResponse::apiCallForFollows() {
	return vector<string>();
}

vector<string> IntStringPairVectorResponse::apiCallForParent() {
	return vector<string>();
}

vector<string> IntStringPairVectorResponse::apiCallForUses() {
	vector< pair<int, string> > result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	if (synonymTable[firstParam] == ASSIGNMENT_VAR) {
		cout << "PKB::getAllAssignmentUsesVariablePairs()" << endl;
		//result = PKB::getAllAssignmentUsesVariablePairs();
	}
	else if (synonymTable[firstParam] == STMT_VAR) {
		cout << "PKB::getAllStmtUsesVariablePairs()" << endl;
		//result = PKB::getAllStmtUsesVariablePairs();
	}
	return getResult(result);
}

vector<string> IntStringPairVectorResponse::apiCallForModifies() {
	vector< pair<int, string> > result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;

	if (synonymTable[firstParam] == ASSIGNMENT_VAR) {
		cout << "PKB::getAllAssignmentModifiesVariablePairs()" << endl;
		//result = PKB::getAllAssignmentModifiesVariablePairs();
	}
	else if (synonymTable[firstParam] == STMT_VAR) {
		cout << "PKB::getAllStmtModifiesVariablePairs()" << endl;
		//result = PKB::getAllStmtModifiesVariablePairs();
	}
	return getResult(result);
}

vector<string> IntStringPairVectorResponse::getResult(vector<pair<int, string>> result) {
	if (result.empty()) return getNoResults();
	if (!selectSynonymIsFoundInParam()) return getImmediateResults();
	return extractedResults(result);
}

vector<string> IntStringPairVectorResponse::extractedResults(vector<pair<int, string>> result) {
	vector<string> extractedResult = selectSynonym == suchThatClause.firstParameter
		? extractFirstParam(result) : extractSecondParam(result);
	return extractedResult;
}

vector<string> IntStringPairVectorResponse::extractFirstParam(vector<pair<int, string>> input) {
	vector<string> strVector;
	for (pair<int, string> i : input) {
		strVector.push_back(to_string(i.first));
	}
	return strVector;
}

vector<string> IntStringPairVectorResponse::extractSecondParam(vector<pair<int, string>> input) {
	vector<string> strVector;
	for (pair<int, string> i : input) {
		strVector.push_back(i.second);
	}
	return strVector;
}