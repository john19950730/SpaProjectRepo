#pragma once
#include "QueryTree.h"

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

class EntityAliasTable;

class QueryPreprocessor {
public:
	static EntityAliasTable entityAliasTable;
	static QueryTree* parseQuery(string query);

private:
	static QueryTree* buildQueryTree(vector<string> queryParts);
	
	static std::vector<std::string> splitByDelimiter(string s, string delimiter);
	static inline void ltrim(string &s);
	static inline void rtrim(std::string &s);
	static inline std::string trim_copy(string s);
};