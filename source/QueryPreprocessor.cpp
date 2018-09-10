#include "QueryPreprocessor.h"
#include "QueryObject.h"
#include "Utility.h"
#include "Keywords.h"

QueryPreprocessor::QueryPreprocessor()
{
	entityAliases = {};
	relParamTypes = {};
	queryObject = new QueryObject();

	vector<string> usesModParam1 = { keywords::query::STMT_VAR, keywords::query::PROC_VAR };
	vector<string> usesModParam2 = { keywords::query::VARIABLE_VAR };
	vector<string> followsParentParam1 = { keywords::query::STMT_VAR };
	vector<string> followsParentParam2 = { keywords::query::STMT_VAR };

	relParamTypes["Uses"] = make_pair(usesModParam1, usesModParam2);
	relParamTypes["Modifies"] = make_pair(usesModParam1, usesModParam2);
	relParamTypes["Follows"] = make_pair(followsParentParam1, followsParentParam2);
	relParamTypes["Parent"] = make_pair(followsParentParam1, followsParentParam2);
}

bool QueryPreprocessor::parseQuery(string query)
{
	if (!isValidQuery(query)) {
		cout << endl;
		cout << "##### Query syntax not valid!" << endl;
		return false;
	}
	if (!buildQueryObject(query)) {
		cout << endl;
		cout << "##### Query not valid!" << endl;
		return false;
	}

	// [SOLVED] doesn't print/access properly (only for select clause)
	cout << "Testing parsing: " << endl;
	SELECT_VAR_CLAUSE selectClause = queryObject->getSelectClause();
	cout << "Variable name: " << selectClause.variableName << endl;
	// cout << queryObject->getSelectClause()->variableName << endl;

	return true;
}

bool QueryPreprocessor::buildQueryObject(string query) {
	if (!isValidResultClause(query))
		return false;
	SELECT_VAR_CLAUSE resultsClause = createResultsClause(query);
	queryObject->setSelectClause(resultsClause);

	regex relSyntax(REL_REGEX);
	smatch matches;
	while (regex_search(query, matches, relSyntax)){
		string relationship = matches[1];
		string param1 = matches[2];
		string param2 = matches[3];
		if (isRelationshipParamsValid(relationship, param1, param2)) {
			if (relationship == "Uses" || relationship == "Uses*") {
				STMT_PROC_VAR_RS_CLAUSE usesClause = createStmtProcVarRsClause(relationship, param1, param2);
				queryObject->setUsesClause(usesClause);
			}
			else if (relationship == "Modifies" || relationship == "Modifies*") {
				STMT_PROC_VAR_RS_CLAUSE modifiesClause = createStmtProcVarRsClause(relationship, param1, param2);
				queryObject->setModifiesClause(modifiesClause);
			}
			else if (relationship == "Follows" || relationship == "Follows*") {
				STMT_RS_CLAUSE followsClause = createStmtRsClause(relationship, param1, param2);
				queryObject->setFollowsClause(followsClause);
			}
			else if (relationship == "Parent" || relationship == "Parent*") {
				STMT_RS_CLAUSE parentClause = createStmtRsClause(relationship, param1, param2);
				queryObject->setParentClause(parentClause);
			}
		}
		query = matches.suffix();
	}
	return true;
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

	// check if select clause is valid
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
	return regex_match(selectClause, selectSyntax);
}

SELECT_VAR_CLAUSE QueryPreprocessor::createResultsClause(string query) {
	SELECT_VAR_CLAUSE clause;
	regex selectSyntax(RESULT_REGEX);
	smatch matches;
	regex_search(query, matches, selectSyntax);
	string aliasType = entityAliases[matches[1].str()];
	string aliasName = matches[1].str();
	clause = { aliasType, aliasName };
	return clause;
}

STMT_PROC_VAR_RS_CLAUSE QueryPreprocessor::createStmtProcVarRsClause(string relationship, string param1, string param2) {
	STMT_PROC_VAR_RS_CLAUSE clause;
	regex transSyntax(TRANS_REGEX);
	smatch matches;
	bool hasTransitiveClosure = false;
	if (regex_search(relationship, matches, transSyntax)) {
		hasTransitiveClosure = true;
	}
	clause = { param1, param2, hasTransitiveClosure };
	return clause;
}

STMT_RS_CLAUSE QueryPreprocessor::createStmtRsClause(string relationship, string param1, string param2) {
	STMT_RS_CLAUSE clause;
	regex transSyntax(TRANS_REGEX);
	smatch matches;
	bool hasTransitiveClosure = false;
	if (regex_search(relationship, matches, transSyntax)) {
		hasTransitiveClosure = true;
	}
	clause = { stoi(param1), stoi(param2), hasTransitiveClosure };
	return clause;
}

bool QueryPreprocessor::isValidResultClause(string query) {
	regex selectSyntax(RESULT_REGEX);
	smatch matches;
	if (regex_search(query, matches, selectSyntax)) {
		// Search hashmap to check if alias exists
		if (entityAliases.count(matches[1].str()) != 1) {
			return false; // not found
		}
	}
	return true;
}

bool QueryPreprocessor::isRelationshipParamsValid(string relationship, string param1, string param2) {
	string paramType1 = getParameterType(param1);
	string paramType2 = getParameterType(param2);
	/*cout << "param1: " << param1 << endl;
	cout << "param2: " << param2 << endl;
	cout << "paramType1: " << paramType1 << endl;
	cout << "paramType2: " << paramType2 << endl;*/
	if (paramType1 == "" || paramType2 == "") return false;

	regex rel("([a-zA-Z]+)[*]?");
	smatch matches;
	if (regex_match(relationship, matches, rel)) {
		relationship = matches[1].str();
	}
	vector<string> expectedParam1 = relParamTypes[relationship].first;
	vector<string> expectedParam2 = relParamTypes[relationship].second;

	bool paramValid1 = false;
	bool paramValid2 = false;

	for (size_t i = 0; i < expectedParam1.size(); i++) {
		if (paramType1 == expectedParam1[i]) {
			paramValid1 = true;
			break;
		}
	}

	for (size_t i = 0; i < expectedParam2.size(); i++) {
		if (paramType2 == expectedParam2[i]) {
			paramValid2 = true;
			break;
		}
	}

	/*cout << "paramValid1: " << paramValid1 << endl;
	cout << "paramValid2: " << paramValid2 << endl;*/

	return paramValid1 && paramValid2;
}

string QueryPreprocessor::getParameterType(string param) {
	if (Utility::isInteger(param)) {
		return keywords::query::STMT_VAR;
	}
	regex doubleQuotes("[\"].*[\"]");
	if (regex_match(param, doubleQuotes)) {
		return keywords::query::VARIABLE_VAR;
	}
	if (entityAliases.count(param) == 1) {
		return entityAliases[param];
	}

	return "";
}

