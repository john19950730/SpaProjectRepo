#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

const string QUERY_SYNTAX_REGEX = "^(?:[\\s]*(?:assign|variable|stmt|procedure|while)[\\s+](?:[a-zA-Z_][a-zA-Z0-9]*(?:[\\s]*[,][\\s]*[a-zA-Z_][a-zA-Z0-9]*)*)[\\s]*[;][\\s]*)*(?:[Ss]elect[\\s]+[a-zA-Z_][a-zA-Z0-9]*(?:[,][\\s]*[a-zA-Z_][a-zA-Z0-9]*)*(?:[\\s]+such that[\\s]+(?:Uses|Modifies|Follows|Parent)[*]?[(](?:[a-zA-Z_][a-zA-Z0-9]*|[0-9]+|[\"].*[\"])[\\s]*[,][\\s]*(?:[a-zA-Z_][a-zA-Z0-9]*|[0-9]+|[\"].*[\"])[)])*)*[;]?$";
const string DECL_REGEX = "(assign|variable|stmt|procedure|while)[\\s+]([a-zA-Z_][a-zA-Z0-9]*(?:[\\s]*[,][\\s]*[a-zA-Z_][a-zA-Z0-9]*)*)[;]?";
const string RESULT_REGEX = "[Ss]elect[\\s]+((?:[a-zA-Z_][a-zA-Z0-9]*)(?:(?:[\\s]*[,][\\s]*)(?:[a-zA-Z_][a-zA-Z0-9]*))*)";
const string REL_REGEX = "(?:((?:Uses|Modifies|Follows|Parent)[*]?)[(]([a-zA-Z_][a-zA-Z0-9]*|[0-9]+|[\"].*[\"])(?:[\\s]*[,][\\s]*)([a-zA-Z_][a-zA-Z0-9]*|[0-9]+|[\"].*[\"])[)])";
const string TRANS_REGEX = "[*]$";

struct SUCH_THAT_CLAUSE;

class QueryObject;

class QueryPreprocessor {
public:
	QueryPreprocessor();
	bool parseQuery(string query);
	QueryObject* getQueryObject();

private:
	QueryObject *queryObject;
	map<string, string> synonymTable;
	map<string, pair<vector<string>, vector<string>>> relParamTypes;

	bool buildQueryObject(string query);
	bool isValidQuerySyntax(string query);
	bool extractSynonymsFromDeclaration(string query);
	bool isValidResultsClause(string query);
	bool isRelationshipParamsValid(string relationship, string param1, string param2);
	
	bool isSynonym(string param);
	string getParameterType(string param);
	string stripDoubleQuotes(string param);

	vector<string> createResultsClause(string query);
	SUCH_THAT_CLAUSE createSuchThatClause(string relationship, string param1, string param2);

};