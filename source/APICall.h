#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

class APICall {
public:
	static vector<string> apiCallForNoClause(string synonymType);
protected:
	string selectSynonym;
	map<string, string> synonymTable;
	pair<string, string> paramType;

	vector<string> getImmediateResults();
	vector<string> getNoResults();
	static vector<string> immediateResults(string synonymType);

	void setSelectSynonym(string selectSynonym);
	void setSynonymTable(map<string, string> synonymTable);
	void setParamType(pair<string, string> paramType);
};