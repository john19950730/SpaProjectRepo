#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

const string SPACE = "[\\s]+";						// One or more spaces
const string COMMA = "[\\s]*[,][\\s]*";				// Comma (padded by zero or more spaces)
const string SEMICOLON = "[\\s]*[;][\\s]*";			// Semicolon (padded by zero or more spaces)
const string SEMICOLON_OPT = "[\\s]*[;]?[\\s]*";	// Semicolon (optional; padded by zero or more spaces)
const string BRACKET_O = "[\\s]*[(][\\s]*";			// Open bracket (padded by zero or more spaces)
const string BRACKET_C = "[\\s]*[)][\\s]*";			// Close bracket (padded by zero or more spaces)
const string SYNONYM = "[a-zA-Z_][a-zA-Z0-9]*";		// Synonym
const string NUMBER = "[0-9]+";						// Number
const string STRING = "[\"].+[\"]";					// One or more characters enclosed in double quotes

const string DECL_DE = "assign|variable|stmt|procedure|while|read|print|call|constant";		// Design entities
const string REL = "Uses|Modifies";															// Relationships (that don't support transitive closure)
const string REL_T = "Follows|Parent";														// Relationships (that support transitive closure)
const string REL_PARAM = SYNONYM + '|' + NUMBER + '|' + STRING;								// Possible relationshp parameter
const string ASTERISK = "[*]?";																// Asterisk to indicate transitive closure

const string DECL_REGEX = '(' + DECL_DE + ')' + SPACE + '(' + SYNONYM + "(?:" + COMMA + SYNONYM + ")*)" + SEMICOLON;
const string RESULT_REGEX = "[Ss]elect" + SPACE + "((?:" + SYNONYM + ")(?:" + COMMA + SYNONYM + ")*)";
const string REL_REGEX = '(' + REL + "|(?:" + REL_T + ")" + ASTERISK + ')' + BRACKET_O + "(?:(" + REL_PARAM + ')' + COMMA + '(' + REL_PARAM + "))" + BRACKET_C;
const string SUCH_THAT = SPACE + "such" + SPACE + "that" + SPACE + "(?:" + REL_REGEX + ")*";
const string QUERY_SYNTAX_REGEX = "^((" + DECL_REGEX + ")*" + '(' + RESULT_REGEX + "(?:" + SUCH_THAT + ")*)*)" + SEMICOLON_OPT + '$';

const string TRANS_REGEX = "[*]$";	// To check for transitive closure

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
	bool isTypeOfStatement(string param);
	string getParameterType(string param);
	string stripDoubleQuotes(string param);

	vector<string> createResultsClause(string query);
	SUCH_THAT_CLAUSE createSuchThatClause(string relationship, string param1, string param2);

};