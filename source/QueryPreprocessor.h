#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class EntityAliasTable;

class QueryPreprocessor {
public:
	static EntityAliasTable entityAliasTable;
	static bool parseQuery(string query);

private:
	static bool buildQueryTree(vector<string> queryParts);
	
	static std::vector<std::string> splitByDelimiter(string s, string delimiter);
	static inline void ltrim(string &s);
	static inline void rtrim(std::string &s);
	static inline std::string trim_copy(string s);
};