#include "QueryPreprocessor.h"
#include "QueryObject.h"
#include "Utility.h"
#include "Keywords.h"

bool QueryPreprocessor::parseQuery(string query)
{
	// initialise QueryObject here
	if (!isValidQuery(query)) {
		cout << endl;
		cout << "##### Query not valid!" << endl;
		return false;
	}
	buildQueryObject(query);
	return false;
}

QueryObject* QueryPreprocessor::buildQueryObject(string query) {
	QueryObject *queryObject = new QueryObject();
	SELECT_VAR_CLAUSE *selectStmt = extractResultClause(query);
	regex relSyntax(REL_REGEX);
	smatch matches;

	while (regex_search(query, matches, relSyntax)){
		string relationship = matches[1];
		string param1 = matches[2];
		string param2 = matches[3];
		/*
		if (relationship == "Uses") {
			// get STMT_PROC_VAR_RS_CLAUSE
		}
		else if (relationship == "Modifies") {
			// get STMT_PROC_VAR_RS_CLAUSE
		}
		else if (relationship == "Follows") {
			// get STMT_RS_CLAUSE
		}
		else if (relationship == "Parent") {
			// get STMT_RS_CLAUSE
		}*/
		query = matches.suffix();
	}

	return new QueryObject();
}

// Checks all statements in query are valid
bool QueryPreprocessor::isValidQuery(string query) {	
	vector<string> queryStatements = Utility::splitByDelimiter(query, ";");
	for (size_t i = 0; i < queryStatements.size(); i++) {
		bool result = isValidStatement(queryStatements[i]);
		if (!result) return false;
	}
	return true;
}


bool QueryPreprocessor::isValidStatement(string statement) {
	regex delimiters("[^\\s,]+"); // wip - need to remove multiple whitespace
	vector<string> tokens = Utility::splitByRegex(statement, delimiters);

	// cannot have 1 or less tokens in a single statement
	if (tokens.size() <= 1)
		return false;

	string keyword = tokens[0];

	if (Utility::matchesDesignEntityKeyword(keyword)) {
		// is a declaration statement -> check if valid
		return isValidDeclaration(keyword, tokens);
	}

	// wip - validate select clauses
	if (keyword == keywords::query::SELECT_VAR) {
		return isValidSelectClauseSyntax(statement);
	}

	return false;
}

bool QueryPreprocessor::isValidDeclaration(string keyword, vector<string> tokens)
{
	// validate declaration statements
	for (size_t i = 1; i < tokens.size(); i++) {
		string alias = tokens[i];
		if (!Utility::isValidVariableName(alias)) // not a valid alias/var name
			return false;
		entityAliases[alias] = keyword; // add alias to table for future reference
	}
	return true;
}

bool QueryPreprocessor::isValidSelectClauseSyntax(string selectClause) {
	regex selectSyntax(SELECT_SYNTAX_REGEX);
	bool isValidOverallSyntaxBool = regex_match(selectClause, selectSyntax);
	return isValidOverallSyntaxBool;
}

SELECT_VAR_CLAUSE* QueryPreprocessor::extractResultClause(string query) {
	SELECT_VAR_CLAUSE select;
	SELECT_VAR_CLAUSE *selectPtr;
	regex selectSyntax(RESULT_REGEX);
	smatch matches;
	if (regex_search(query, matches, selectSyntax)) {
		// Search hashmap to check if alias exists
		if (entityAliases.find(matches[1].str()) == entityAliases.end()) {
			return NULL; // not found
		}
		select = { entityAliases[matches[1].str()], matches[1].str() };
	}
	selectPtr = &select;
	//cout << "VarName : " << selectPtr->variableName << endl;
	//cout << "VarType : " << selectPtr->variableType << endl;
	return selectPtr;
}