#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class QueryPreprocessor {
public:
	static bool parseQuery(string query);

private:
	map<string, string> entityAliases;

	static bool isValidStatement(string substatement);
	static bool buildQueryObject(vector<string> queryParts);

};