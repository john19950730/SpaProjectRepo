#include "ApiCallPatternClause.h"
#include "Keywords.h"

using namespace keywords::clauseParamType;

ApiCallPatternClause::ApiCallPatternClause(pair<string, string> paramType, PATTERN_CLAUSE patternClause, string selectSynonym) {
	this->paramType = paramType;
	this->patternClause = patternClause;
	this->selectSynonym = selectSynonym;
}

string ApiCallPatternClause::executeApiCall() {
	if (paramType == make_pair(SYNONYM, EXPRESSION) || paramType == make_pair(SYNONYM, UNDERSCORE)) {

	} 
}

string ApiCallPatternClause::selectResults(bool hasResults, vector<int> results) {
	string patternSynonym = patternClause.synonym;
	if (patternSynonym != selectSynonym) {
		// check if there is results	
	}
	else {
		// select the results - convert vector<int> into string
	}

	return "";
}