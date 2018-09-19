#include "APICallPatternClause.h"
#include "Keywords.h"

using namespace keywords::clauseParamType;

APICallPatternClause::APICallPatternClause(pair<string, string> paramType, PATTERN_CLAUSE patternClause, string selectSynonym, map<string, string> synonymTable) {
	this->patternClause = patternClause;
	this->setParamType(paramType);
	this->setSelectSynonym(selectSynonym);
	this->setSynonymTable(synonymTable);
}

vector<string> APICallPatternClause::executeApiCall() {
	if (paramType == make_pair(SYNONYM, EXPRESSION) || paramType == make_pair(UNDERSCORE, EXPRESSION)) {

	}
	else if (paramType == make_pair(SYNONYM, SYNONYM) || paramType == make_pair(UNDERSCORE, UNDERSCORE)) {

	}
	else if (paramType == make_pair(VARIABLE, EXPRESSION)) {

	}
	else if (paramType == make_pair(VARIABLE, UNDERSCORE)) {

	}

	return vector<string>();
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