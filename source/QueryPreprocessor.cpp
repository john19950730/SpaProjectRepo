#include "QueryPreprocessor.h"
#include "QueryObject.h"
#include "Utility.h"
#include "Keywords.h"

QueryPreprocessor::QueryPreprocessor()
{
	synonymTable = {};
	relParamTypes = {};
	queryObject = new QueryObject();

	vector<SUCH_THAT_CLAUSE> usesClauses;
	vector<SUCH_THAT_CLAUSE> modifiesClauses;
	vector<SUCH_THAT_CLAUSE> followsClauses;
	vector<SUCH_THAT_CLAUSE> parentClauses;
	vector<PATTERN_CLAUSE> patternClauses;

	vector<string> usesModParam1 = { keywords::query::STMT_VAR, keywords::query::PROC_VAR, "_QUOTED" };
	vector<string> usesModParam2 = { keywords::query::VARIABLE_VAR, "_UNDERSCORE", "_QUOTED" };
	vector<string> followsParentParam1 = { keywords::query::STMT_VAR, "_UNDERSCORE" };
	vector<string> followsParentParam2 = { keywords::query::STMT_VAR, "_UNDERSCORE" };

	vector<string> patternParam1 = { keywords::query::VARIABLE_VAR, "_UNDERSCORE", "_QUOTED" };
	vector<string> patternParam2 = { "_UNDERSCORE", "_SUBEXPRESSION", "_QUOTED" };

	relParamTypes["Uses"] = make_pair(usesModParam1, usesModParam2);
	relParamTypes["Modifies"] = make_pair(usesModParam1, usesModParam2);
	relParamTypes["Follows"] = make_pair(followsParentParam1, followsParentParam2);
	relParamTypes["Parent"] = make_pair(followsParentParam1, followsParentParam2);

	relParamTypes["pattern"] = make_pair(patternParam1, patternParam2);
}

bool QueryPreprocessor::parseQuery(string query)
{
	if (!isQuerySyntaxValid(query)) {
		cout << endl << endl << "##### Query syntax is invalid!" << endl;
		cout << endl << "### Example usage:  variable v; procedure v; select v such that Uses(1, v)" << endl;
		cout << "#### keywords are case-sensitive i.e. relationships must begin with an upper-case letter, but 'select' and 'Select' are both accepted" << endl;
		cout << "#### semicolon at the end of `select` clause is optional" << endl << endl;
		return false;
	}
	
	if (!extractSynonymsFromDeclaration(query)) {
		cout << endl << endl << "##### Duplicate synonyms declared! Please check again!" << endl << endl;
		return false;
	}

	if (!buildQueryObject(query)) {
		cout << endl << "##### Query is invalid!" << endl << endl;
		return false;
	}

	return true;
}

QueryObject* QueryPreprocessor::getQueryObject() {
	return this->queryObject;
}

bool QueryPreprocessor::buildQueryObject(string query) {
	if (!setResultsClauseInQueryObject(query))
		return false;
	if(!setRelationhipClausesInQueryObject(query))
		return false;
	if (!setPatternClausesInQueryObject(query))
		return false;

	return true;
}

bool QueryPreprocessor::setResultsClauseInQueryObject(string query) {
	if (!isResultsClauseValid(query)) {
		cout << endl << endl << "### Check that you have declared all used synonyms";
		return false;
	}
	vector<string> resultsClause = createResultsClause(query);
	queryObject->setSelectClause(resultsClause);
	queryObject->setSynonymTable(synonymTable);

	return true;
}

bool QueryPreprocessor::setRelationhipClausesInQueryObject(string query) {
	regex relSyntax(REL_REGEX);
	smatch matches;
	while (regex_search(query, matches, relSyntax)) {
		string relationship = matches[1];
		string param1 = matches[2];
		string param2 = matches[3];

		SUCH_THAT_CLAUSE clause;
		if (areRelationshipParamsValid(relationship, param1, param2)) {
			if (relationship == "Uses") {
				clause = createSuchThatClause(relationship, param1, param2);
				usesClauses.push_back(clause);
				queryObject->setUsesClause(usesClauses);
			}
			else if (relationship == "Modifies") {
				clause = createSuchThatClause(relationship, param1, param2);
				modifiesClauses.push_back(clause);
				queryObject->setModifiesClause(modifiesClauses);
			}
			else if (relationship == "Follows" || relationship == "Follows*") {
				clause = createSuchThatClause(relationship, param1, param2);
				followsClauses.push_back(clause);
				queryObject->setFollowsClause(followsClauses);
			}
			else if (relationship == "Parent" || relationship == "Parent*") {
				clause = createSuchThatClause(relationship, param1, param2);
				parentClauses.push_back(clause);
				queryObject->setParentClause(parentClauses);
			}
		}
		else {
			return false;
		}
		query = matches.suffix();
	}
	return true;
}

bool QueryPreprocessor::setPatternClausesInQueryObject(string query) {
	regex patternSyntax(PATTERN);
	smatch matches;
	PATTERN_CLAUSE clause;
	while (regex_search(query, matches, patternSyntax)) {
		string patternSynonym = matches[1];
		string param1 = matches[2];
		string param2 = matches[3];
		if (isPatternSynonymValid(patternSynonym) && arePatternParamsValid(param1, param2)) {
			cout << ">> " + patternSynonym + '(' + param1 + ", " + param2 + ')' << endl;
			// create pattern clause
			clause = createPatternClause(patternSynonym, param1, param2);
			patternClauses.push_back(clause);
			queryObject->setPatternClause(patternClauses);
		}
		else return false;

		query = matches.suffix();
	}
	return true;
}

// Checks if query syntax is valid
bool QueryPreprocessor::isQuerySyntaxValid(string query) {	
	regex querySyntax(QUERY_SYNTAX_REGEX);
	return regex_match(query, querySyntax);
}

bool QueryPreprocessor::extractSynonymsFromDeclaration(string query) {
	regex declarationSyntax(DECL_REGEX);
	smatch matches;

	while (regex_search(query, matches, declarationSyntax)) {
		string designEntity = matches[1];
		string synonymStr = matches[2];
		vector<string> synonymVctr = Utility::splitByDelimiter(synonymStr, ",");
		for (size_t i = 0; i < synonymVctr.size(); i++)
		{
			if (existsInSynonymTable(synonymVctr[i]))
				return false;
			synonymTable[synonymVctr[i]] = designEntity;
		}
		query = matches.suffix();
	}

	return true;
}

bool QueryPreprocessor::isResultsClauseValid(string query) {
	regex resultSyntax(RESULT_REGEX);
	smatch matches;
	if (regex_search(query, matches, resultSyntax)) {
		// Search hashmap to check if synonym exists
		if (synonymTable.count(matches[1].str()) != 1) {
			return false; // not found
		}
	}
	return true;
}

vector<string> QueryPreprocessor::createResultsClause(string query) {
	vector<string> clause;
	regex resultSyntax(RESULT_REGEX);
	smatch matches;
	regex_search(query, matches, resultSyntax);
	string synonymType = synonymTable[matches[1].str()];
	string synonymName = matches[1].str();
	clause.push_back(synonymName);
	return clause;
}

SUCH_THAT_CLAUSE QueryPreprocessor::createSuchThatClause(string relationship, string param1, string param2) {
	SUCH_THAT_CLAUSE clause;
	regex transSyntax(TRANS_REGEX);
	smatch matches;
	bool hasTransitiveClosure = false;
	if (regex_search(relationship, matches, transSyntax)) {
		hasTransitiveClosure = true;
	}
	bool paramIsSynonym1 = existsInSynonymTable(param1);
	bool paramIsSynonym2 = existsInSynonymTable(param2);
	clause = { stripDoubleQuotes(param1), stripDoubleQuotes(param2),
		hasTransitiveClosure, paramIsSynonym1, paramIsSynonym2 };
	return clause;
}

PATTERN_CLAUSE QueryPreprocessor::createPatternClause(string patternSynonym, string param1, string param2)
{
	PATTERN_CLAUSE clause;

	// check if param1 is synonym
	bool paramIsSynonym1 = existsInSynonymTable(param1);

	// check if param2 is a partial expression
	bool paramIsPartialExpression = false;
	if (param2 != "_" && param2.front() == '_') {
		paramIsPartialExpression = true;
	}

	if (param2 != "_") {
		regex exprSyntax(STRING_CONTENTS);
		smatch exprMatches;
		regex_search(param2, exprMatches, exprSyntax);
		param2 = exprMatches[1].str();
		// convert param2 into postfix
		//string postfix = Utility::convertInfixToPostfix(paramExpr);
		//param2 = postfix;
		//cout << "postfix: " << postfix << endl;
	}

	cout << param2 << endl;

	clause = { patternSynonym, stripDoubleQuotes(param1), param2, paramIsPartialExpression, paramIsSynonym1 };
	return clause;
}

bool QueryPreprocessor::areRelationshipParamsValid(string relationship, string param1, string param2) {
	string paramType1 = getParameterType(param1);
	string paramType2 = getParameterType(param2);
	cout << ">> " + relationship + '(' + param1 + ':' + paramType1 + ", " + param2 + ':' + paramType2 + ')' << endl;
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

	if (!paramValid1) cout << endl << endl << "### 1st parameter in " << relationship << " relationship is invalid";
	if (!paramValid2) cout << endl << endl << "### 2nd parameter in " << relationship << " relationship is invalid";

	return paramValid1 && paramValid2;
}

bool QueryPreprocessor::arePatternParamsValid(string param1, string param2) {
	string paramType1 = getParameterType(param1);
	string paramType2 = getParameterType(param2);
	if (paramType1 == "" || paramType2 == "") return false;

	bool paramValid1 = false;
	bool paramValid2 = false;
	vector<string> expectedParam1 = relParamTypes["pattern"].first;
	vector<string> expectedParam2 = relParamTypes["pattern"].second;
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

	if (paramType2 != "_UNDERSCORE") {
		regex exprSyntax(STRING_CONTENTS);
		smatch matches;
		if (regex_search(param2, matches, exprSyntax)) {
			string expr = matches[1].str();
		}
		else paramValid2 = false;
		/*if (!Utility::validateInfixExpression(expr)) {
			paramValid2 = false;
		}*/
	}

	if (!paramValid1) cout << endl << endl << "### 1st parameter in pattern is invalid";
	if (!paramValid2) cout << endl << endl << "### 2nd parameter in pattern is invalid";

	return paramValid1 && paramValid2;
}

string QueryPreprocessor::getParameterType(string param) {
	if (Utility::isInteger(param)) {
		return keywords::query::STMT_VAR;
	}
	if (param == "_") {
		return "_UNDERSCORE";
	}
	if (param.front() == '"') {
		return "_QUOTED";
	}
	if (param.front() == '_') {
		return "_SUBEXPRESSION";
	}
	if (existsInSynonymTable(param)) {
		if (isATypeOfStatement(synonymTable[param])) {
			// is a type of statement e.g. assign, while, if, etc.
			return keywords::query::STMT_VAR;
		}
		else {
			// could be procedure, constant, variable, etc.
			return synonymTable[param];
		}
	}
	return "";
}

bool QueryPreprocessor::existsInSynonymTable(string synonym) {
	if (synonymTable.count(synonym) == 1) {
		return true;
	}
	return false;
}

bool QueryPreprocessor::isPatternSynonymValid(string synonym) {
	if (existsInSynonymTable(synonym)) {
		vector<string> patternTypes = keywords::query::PATTERN_TYPES;
		for (size_t i = 0; i < patternTypes.size(); i++)
		{
			if (patternTypes[i] == synonymTable[synonym])
				return true;
		}
	}
	return false;
}

bool QueryPreprocessor::isATypeOfStatement(string paramType) {
	vector<string> statementTypes = keywords::query::STATEMENTS;
	for (size_t i = 0; i < statementTypes.size(); i++)
	{
		if (paramType == statementTypes[i])
			return true;
	}
	return false;
}

string QueryPreprocessor::stripDoubleQuotes(string param) {
	if (param.front() == '"') {
		param.erase(0, 1); // erase the first character
		param.erase(param.size() - 1); // erase the last character
	}
	return param;
}
