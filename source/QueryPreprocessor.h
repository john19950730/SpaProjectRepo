#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

class QueryObject;
struct SELECT_VAR_CLAUSE;

const string SELECT_SYNTAX_REGEX = "^[Ss]elect[\\s]+[a-zA-Z_][a-zA-Z0-9]*(?:[,][\\s]*[a-zA-Z_][a-zA-Z0-9]*)*(?:[\\s]+such that[\\s]+(?:Uses|Modifies|Follows|Parent)[*]?[(][a-zA-Z_][a-zA-Z0-9]*[\\s]*[,][\\s]*[a-zA-Z_][a-zA-Z0-9]*[)])*$";
const string RESULT_REGEX = "[Ss]elect[\\s]+((?:[a-zA-Z_][a-zA-Z0-9]*)(?:(?:[\\s]*[,][\\s]*)(?:[a-zA-Z_][a-zA-Z0-9]*))*)";
const string REL_REGEX = "(?:((?:Uses|Modifies|Follows|Parent)[*]?)[(]([a-zA-Z_][a-zA-Z0-9]*)(?:[\\s]*[,][\\s]*)([a-zA-Z_][a-zA-Z0-9]*)[)])";

static map<string, string> entityAliases;

class QueryPreprocessor {
public:
	static bool parseQuery(string query);

private:
	QueryObject *queryObject;

	static QueryObject* buildQueryObject(string query);
	static bool isValidQuery(string query);
	static bool isValidStatement(string substatement);
	static bool isValidDeclaration(string keyword, vector<string> tokens);
	static bool isValidSelectClauseSyntax(string selectClause);
	static SELECT_VAR_CLAUSE* extractResultClause(string selectClause);

};