#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

const string SPACE = "[\\s]+";						// One or more spaces
const string SPACE_OPT = "[\\s]*";
const string COMMA = "[\\s]*[,][\\s]*";				// Comma (padded by zero or more spaces)
const string SEMICOLON = "[\\s]*[;][\\s]*";			// Semicolon (padded by zero or more spaces)
const string SEMICOLON_OPT = "[\\s]*[;]?[\\s]*";	// Semicolon (optional; padded by zero or more spaces)
const string BRACKET_O = "[\\s]*[(][\\s]*";			// Open bracket (padded by zero or more spaces)
const string BRACKET_C = "[\\s]*[)]";				// Close bracket (beginning padded by zero or more spaces)
const string SYNONYM = "[a-zA-Z][a-zA-Z0-9]*";		// Synonym
const string NUMBER = "[0-9]+";						// Number
const string UNDERSCORE = "[_]";					// Underscore
const string STRING = "\"[^\"]*\"";					// One or more characters enclosed in double quotes

const string DECL_DE = "assign|variable|stmt|procedure|while|if|read|print|call|constant";		// Design entities
const string REL = "Uses|Modifies";																// Relationships (that don't support transitive closure)
const string REL_T = "Follows|Parent";															// Relationships (that support transitive closure)
const string REL_PARAM = SYNONYM + '|' + UNDERSCORE + '|' + NUMBER + '|' + STRING;								// Possible relationshp parameter
const string ASTERISK = "[*]?";																	// Asterisk to indicate transitive closure
const string PATTERN_PARAM = UNDERSCORE + '|' + UNDERSCORE + STRING + UNDERSCORE;

const string DECL_REGEX = '(' + DECL_DE + ')' + SPACE + '(' + SYNONYM + "(?:" + COMMA + SYNONYM + ")*)" + SEMICOLON;
const string RESULT_REGEX = "Select" + SPACE + "((?:" + SYNONYM + ")(?:" + COMMA + SYNONYM + ")*)";
const string REL_REGEX = '(' + REL + "|(?:" + REL_T + ")" + ASTERISK + ')' + BRACKET_O + "(?:(" + REL_PARAM + ')' + COMMA + '(' + REL_PARAM + "))" + BRACKET_C;
const string SUCH_THAT_REGEX = SPACE + "such" + SPACE + "that" + SPACE + "(?:" + REL_REGEX + ")";
const string PATTERN_REGEX = SPACE + "pattern" + SPACE + '(' + SYNONYM + ')' + BRACKET_O + '(' + REL_PARAM + ')' + COMMA + '(' + PATTERN_PARAM + ')' + BRACKET_C;
const string QUERY_SYNTAX_REGEX = '^' + SPACE_OPT + "(?:(?:" + DECL_REGEX + ")*" + "(?:" + RESULT_REGEX + "(?:" + SUCH_THAT_REGEX + '|' + PATTERN_REGEX + ")*))" + SPACE_OPT + '$';

/* Helper regex definitions */
const string IS_TRANS_REGEX = "[*]$";															// To check for transitive closure
const string GET_REL_TYPE_REGEX = "([a-zA-Z]+)[*]?";											// To extract the relationship type without any '*' e.g. "Follows" from "Follows*"
const string GET_STRING_CONTENTS = "\"([^\"0-9\\W_]*(?:" + SYNONYM + '|' + NUMBER + "))\"";		// To extract text between double quotes

struct SUCH_THAT_CLAUSE;
struct PATTERN_CLAUSE;

class QueryObject;

class QueryPreprocessor {
public:
	QueryPreprocessor();
	bool parseQuery(string query);
	QueryObject* getQueryObject();

	vector<SUCH_THAT_CLAUSE> usesClauses;
	vector<SUCH_THAT_CLAUSE> modifiesClauses;
	vector<SUCH_THAT_CLAUSE> followsClauses;
	vector<SUCH_THAT_CLAUSE> parentClauses;
	vector<PATTERN_CLAUSE> patternClauses;

private:
	QueryObject *queryObject;
	map<string, string> synonymTable;
	map<string, pair<vector<string>, vector<string>>> clauseParamTypeTable;

	bool buildQueryObject(string query);
	bool setResultsClauseInQueryObject(string query);
	bool setRelationhipClausesInQueryObject(string query);
	bool setPatternClausesInQueryObject(string query);

	bool isQuerySyntaxValid(string query);
	bool extractSynonymsFromDeclaration(string query);
	bool isResultsClauseValid(string query);
	bool areRelationshipParamsValid(string relationship, string param1, string param2);
	bool arePatternParamsValid(string param1, string param2);
	
	bool existsInSynonymTable(string param);
	bool isPatternSynonymValid(string synonym);
	bool isATypeOfStatement(string paramType);
	string getParameterType(string param);
	string stripDoubleQuotes(string param);

	vector<string> createResultsClause(string query);
	SUCH_THAT_CLAUSE createSuchThatClause(string relationship, string param1, string param2);
	PATTERN_CLAUSE createPatternClause(string patternSynonym, string param1, string param2);

};