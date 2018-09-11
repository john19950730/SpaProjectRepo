#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

const string QUERY_SYNTAX_REGEX = "^(?:[\\s]*(?:assign|variable|stmt|procedure|while)[\\s+](?:[a-zA-Z_][a-zA-Z0-9]*(?:[\\s]*[,][\\s]*[a-zA-Z_][a-zA-Z0-9]*)*)[\\s]*[;][\\s]*)*(?:[Ss]elect[\\s]+[a-zA-Z_][a-zA-Z0-9]*(?:[,][\\s]*[a-zA-Z_][a-zA-Z0-9]*)*(?:[\\s]+such that[\\s]+(?:Uses|Modifies|Follows|Parent)[*]?[(](?:[a-zA-Z_][a-zA-Z0-9]*|[0-9]+|[\"].*[\"])[\\s]*[,][\\s]*(?:[a-zA-Z_][a-zA-Z0-9]*|[0-9]+|[\"].*[\"])[)])*)*[;]?$";
const string DECL_REGEX = "(assign|variable|stmt|procedure|while)[\\s+]([a-zA-Z_][a-zA-Z0-9]*(?:[\\s]*[,][\\s]*[a-zA-Z_][a-zA-Z0-9]*)*)[;]";
const string RESULT_REGEX = "[Ss]elect[\\s]+((?:[a-zA-Z_][a-zA-Z0-9]*)(?:(?:[\\s]*[,][\\s]*)(?:[a-zA-Z_][a-zA-Z0-9]*))*)";
const string REL_REGEX = "(?:((?:Uses|Modifies|Follows|Parent)[*]?)[(]([a-zA-Z_][a-zA-Z0-9]*|[0-9]+|[\"].*[\"])(?:[\\s]*[,][\\s]*)([a-zA-Z_][a-zA-Z0-9]*|[0-9]+|[\"].*[\"])[)])";
const string TRANS_REGEX = "[*]$";

struct SELECT_VAR_CLAUSE;
struct STMT_PROC_VAR_RS_CLAUSE;
struct STMT_RS_CLAUSE;

class QueryObject;

class QueryPreprocessor {
public:
	QueryPreprocessor();
	bool parseQuery(string query);
	QueryObject* getQueryObject();

private:
	QueryObject *queryObject;
	map<string, string> entityAliases;
	map<string, pair<vector<string>, vector<string>>> relParamTypes;

	bool buildQueryObject(string query);
	bool isValidQuery(string query);
	bool extractAliasesFromDeclaration(string query);
	bool isValidResultsClause(string query);
	bool isRelationshipParamsValid(string relationship, string param1, string param2);
	string getParameterType(string param);

	SELECT_VAR_CLAUSE createResultsClause(string query);
	STMT_PROC_VAR_RS_CLAUSE createStmtProcVarRsClause(string relationship, string param1, string param2);
	STMT_RS_CLAUSE createStmtRsClause(string relationship, string param1, string param2);

};