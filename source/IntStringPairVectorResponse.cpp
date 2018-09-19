#include "IntStringPairVectorResponse.h"
#include "PKB.h"
#include "Keywords.h"

using namespace keywords::clauseParamType;
using namespace keywords::query;

IntStringPairVectorResponse::IntStringPairVectorResponse() : APICallSuchThatClause() {}

vector<string> IntStringPairVectorResponse::apiCallForFollows() {
	return vector<string>();
}

vector<string> IntStringPairVectorResponse::apiCallForParent() {
	return vector<string>();
}

vector<string> IntStringPairVectorResponse::apiCallForUses() {
	vector< pair<unsigned int, string> > result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	vector<string> results;

	// First synonym is of statement type - second param is definitely variable synonym type
		
	//result = PKB::getAllStmtUsesVariablePairs(synonymTable[firstParam]); // Uses(a, v)
	results.push_back("PKB::getAllStmtUsesVariablePairs(synonymTable[firstParam]); // Uses(a, v)");

	return results;
}

vector<string> IntStringPairVectorResponse::apiCallForModifies() {
	vector< pair<unsigned int, string> > result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	vector<string> results;
	
	// First synonym is of statement type - second param is definitely variable synonym type
	
	//result = PKB::getAllStmtModifiesVariablePairs(synonymTable[firstParam]); // Modifies(a, v)
	results.push_back("PKB::getAllStmtModifiesVariablePairs(synonymTable[firstParam]); // Modifies(a, v)");

	return results;
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