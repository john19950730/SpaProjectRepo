#include "QueryPreprocessor.h"
#include "Utility.h"
#include "Keywords.h"

bool QueryPreprocessor::parseQuery(string query)
{
	vector<string> queryStatements = Utility::splitByDelimiter(query, ";");
	for (size_t i = 0; i < queryStatements.size(); i++) {
		cout << queryStatements[i] << endl;
		cout << isValidStatement(queryStatements[i]) << endl;
	}
	return false;
}

bool QueryPreprocessor::buildQueryObject(vector<string> queryStatements) {	
	return false;
}

bool QueryPreprocessor::isValidStatement(string statement) {
	map<string, string> entityAliases;
	
	regex delimiters("[^\\s,]+"); // wip - need to remove multiple whitespace
	vector<string> tokens = Utility::splitByRegex(statement, delimiters);

	// cannot have 1 or less tokens in a single statement
	if (tokens.size() <= 1)
		return false;

	string keyword = tokens[0];

	// validate declaration statements
	if (Utility::matchesDesignEntityKeyword(keyword))  {
		for (size_t i = 1; i < tokens.size(); i++) {
			string alias = tokens[i];
			if (!Utility::isValidVariableName(alias)) // not a valid alias/var name
				return false;
			entityAliases[alias] = keyword; // add alias to table for future reference
		}
		cout << entityAliases["a1"] << endl;
		return true;
	}

	// wip - validate select clauses
	if (keyword == keywords::query::SELECT_VAR) {
		return true;
	}

	return false;
}