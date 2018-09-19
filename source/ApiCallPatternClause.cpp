#include "APICallPatternClause.h"
#include "Keywords.h"
#include "PKB.h"

using namespace keywords::query;
using namespace keywords::clauseParamType;

APICallPatternClause::APICallPatternClause(pair<string, string> paramType, PATTERN_CLAUSE patternClause, string selectSynonym, map<string, string> synonymTable) {
	this->patternClause = patternClause;
	this->setParamType(paramType);
	this->setSelectSynonym(selectSynonym);
	this->setSynonymTable(synonymTable);
}

vector<string> APICallPatternClause::executeApiCall() {
	if (paramType == make_pair(VARIABLE, UNDERSCORE) || paramType == make_pair(UNDERSCORE, CONSTANT) || paramType == make_pair(UNDERSCORE, VARIABLE)
		|| paramType == make_pair(VARIABLE, CONSTANT) || paramType == make_pair(VARIABLE, VARIABLE)) {
		return getIntVectorResponse();
	}
	else if (paramType == make_pair(UNDERSCORE, UNDERSCORE)) {
		return getBooleanResponse();
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE) || paramType == make_pair(SYNONYM, CONSTANT)
		|| paramType == make_pair(SYNONYM, VARIABLE)) {
		return getIntStringVectorResponse();
	}

	return vector<string>();
}

vector<string> APICallPatternClause::getIntVectorResponse() {
	vector<unsigned int> result;
	vector<string> results;

	if (paramType == make_pair(VARIABLE, UNDERSCORE)) { // a("v", _)
		// Becomes Modifies(a, "v") 
		//result = PKB::getAllStmtThatModifiesVariable(ASSIGNMENT_VAR, patternClause.firstParam);
		results.push_back("PKB::getAllStmtThatModifiesVariable(ASSIGNMENT_VAR, patternClause.firstParam) // Modifies(a, 'v') ");
	}
	else if (paramType == make_pair(UNDERSCORE, CONSTANT)) { // a(_, _"5"_)
		// Uses(a, "5")
	}
	else if (paramType == make_pair(UNDERSCORE, VARIABLE)) { // a(_,_"var"_)
		// Uses(a, "var")
		//result = PKB::getAllStmtsThatUsesVariable(ASSIGNMENT_VAR, patternClause.secondParam);
		results.push_back("PKB::getAllStmtsThatUsesVariable(ASSIGNMENT_VAR, patternClause.secondParam) // Uses(a, 'var')");
	}
	else if (paramType == make_pair(VARIABLE, CONSTANT)) { // a('v', _'5'_)
		// Modifies(a,"v") - Get all assignments that modifies "v"
		// Uses(a, "5") - Loop through all assignments and get the assignment that uses constant 5
	}
	else if (paramType == make_pair(VARIABLE, VARIABLE)) { // a('v', _'h'_)
		// Modifies(a,"v") - Get all assignments that modifies "v"
		// Uses(a, "h") - Loop through all assignments and get the assignment that uses variable h
	}
	return results;
}

vector<string> APICallPatternClause::getBooleanResponse() {
	// a(_,_)
	return vector<string>();

}

vector<string> APICallPatternClause::getIntStringVectorResponse() {
	vector< pair<unsigned int, string> > result;
	vector<string> results;

	if (paramType == make_pair(SYNONYM, UNDERSCORE)) {	// a(v, _)
		// Modifies(a, v)
		result = PKB::getAllStmtModifiesVariablePairs(ASSIGNMENT_VAR);
		results.push_back("PKB::getAllStmtModifiesVariablePairs(ASSIGNMENT_VAR) // a(v, _)");
	}
	else if (paramType == make_pair(SYNONYM, CONSTANT)) { // a(v, _'5'_)
		// Modifies(a, v)
		PKB::getAllStmtModifiesVariablePairs(ASSIGNMENT_VAR);
		// Uses(a, "5")
		results.push_back("PKB::getAllStmtModifiesVariablePairs(ASSIGNMENT_VAR) // a(v, _'5'_)");
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) { // a(v,_'h'_)
		// Modifies(a, v)
		PKB::getAllStmtModifiesVariablePairs(ASSIGNMENT_VAR);
		
		// Uses(a, "h")
		results.push_back("PKB::getAllStmtModifiesVariablePairs(ASSIGNMENT_VAR) // a(v,_'h'_)");
	}

	return results;
}

vector<string> APICallPatternClause::selectResults(bool hasResults, vector<int> results) {
	string patternSynonym = patternClause.synonym;
	if (!hasResults) return getNoResults();

	if (patternSynonym != selectSynonym) {
		return getImmediateResults();
	}
	else {
		//return intVectorToString(results); // select the results - convert vector<int> into string
		return convertVectorIntToVectorStr(results);
	}
}

string APICallPatternClause::intVectorToString(vector<int> input) {
	string s = "";
	for (int i : input) {
		s += " " + to_string(i);
	}
	return s;
}

vector<string> APICallPatternClause::convertVectorIntToVectorStr(vector<int> input) {
	vector<string> strVector;
	for (int i : input) {
		strVector.push_back(to_string(i));
	}
	return strVector;
}