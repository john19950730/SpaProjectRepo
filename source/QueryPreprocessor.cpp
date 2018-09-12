#include "QueryPreprocessor.h"
#include "QueryObject.h"
#include "Utility.h"
#include "Keywords.h"

QueryPreprocessor::QueryPreprocessor()
{
	entityAliases = {};
	relParamTypes = {};
	queryObject = new QueryObject();

	vector<string> usesModParam1 = { keywords::query::STMT_VAR, keywords::query::PROC_VAR, "_NAME" };
	vector<string> usesModParam2 = { keywords::query::VARIABLE_VAR, "_NAME" };
	vector<string> followsParentParam1 = { keywords::query::STMT_VAR };
	vector<string> followsParentParam2 = { keywords::query::STMT_VAR };

	relParamTypes["Uses"] = make_pair(usesModParam1, usesModParam2);
	relParamTypes["Modifies"] = make_pair(usesModParam1, usesModParam2);
	relParamTypes["Follows"] = make_pair(followsParentParam1, followsParentParam2);
	relParamTypes["Parent"] = make_pair(followsParentParam1, followsParentParam2);
}

QueryObject* QueryPreprocessor::getQueryObject() {
	return this->queryObject;
}

bool QueryPreprocessor::parseQuery(string query)
{
	if (!isValidQuery(query)) {
		cout << endl << endl << "##### Query syntax is invalid!" << endl;
		cout << endl << "### Example usage:  variable v; procedure v; select v such that Uses(1, v)" << endl;
		cout << "#### keywords are case-sensitive i.e. relationships must begin with an upper-case letter, but 'select' and 'Select' are both accepted" << endl;
		cout << "#### semicolon at the end of `select` clause is optional" << endl << endl;
		return false;
	}
	
	extractAliasesFromDeclaration(query);

	if (!buildQueryObject(query)) {
		cout << endl << "##### Query is invalid!" << endl << endl;
		return false;
	}

	return true;
}

bool QueryPreprocessor::buildQueryObject(string query) {
	if (!isValidResultsClause(query)) {
		cout << endl << endl << "### Check that you have declared all used synonyms";
		return false;
	}
	vector<string> resultsClause = createResultsClause(query);
	queryObject->setSelectClause(resultsClause);

	vector<SUCH_THAT_CLAUSE> usesClauses; // Added
	vector<SUCH_THAT_CLAUSE> modifiesClauses; // Added
	vector<SUCH_THAT_CLAUSE> followsClauses; // Added
	vector<SUCH_THAT_CLAUSE> parentClauses; // Added

	regex relSyntax(REL_REGEX);
	smatch matches;
	while (regex_search(query, matches, relSyntax)){
		string relationship = matches[1];
		string param1 = matches[2];
		string param2 = matches[3];
		SUCH_THAT_CLAUSE clause;
		if (isRelationshipParamsValid(relationship, param1, param2)) {
			if (relationship == "Uses" || relationship == "Uses*") {
				clause = createSuchThatClause(relationship, param1, param2); // Modified
				usesClauses.push_back(clause); // Added
				queryObject->setUsesClause(usesClauses); // Modified
			}
			else if (relationship == "Modifies" || relationship == "Modifies*") {
				clause = createSuchThatClause(relationship, param1, param2); // Modified
				modifiesClauses.push_back(clause); // Added
				queryObject->setModifiesClause(modifiesClauses); // Modified
			}
			else if (relationship == "Follows" || relationship == "Follows*") {
				clause = createSuchThatClause(relationship, param1, param2); // Modified
				followsClauses.push_back(clause); // Added
				queryObject->setFollowsClause(followsClauses); // Modified
			}
			else if (relationship == "Parent" || relationship == "Parent*") {
				clause = createSuchThatClause(relationship, param1, param2); // Modified
				parentClauses.push_back(clause); // Added
				queryObject->setParentClause(parentClauses); // Modified
			}
		}
		else {
			return false;
		}
		query = matches.suffix();
	}
	return true;
}

// Checks if query syntax is valid
bool QueryPreprocessor::isValidQuery(string query) {	
	regex querySyntax(QUERY_SYNTAX_REGEX);
	return regex_match(query, querySyntax);
}

bool QueryPreprocessor::extractAliasesFromDeclaration(string query) {
	regex declarationSyntax(DECL_REGEX);
	smatch matches;

	while (regex_search(query, matches, declarationSyntax)) {
		string designEntity = matches[1];
		string aliasStr = matches[2];
		vector<string> aliasVctr = Utility::splitByDelimiter(aliasStr, ",");
		for (size_t i = 0; i < aliasVctr.size(); i++)
		{
			entityAliases[aliasVctr[i]] = designEntity;
		}
		query = matches.suffix();
	}

	return true;
}

bool QueryPreprocessor::isValidResultsClause(string query) {
	regex resultSyntax(RESULT_REGEX);
	smatch matches;
	if (regex_search(query, matches, resultSyntax)) {
		// Search hashmap to check if alias exists
		if (entityAliases.count(matches[1].str()) != 1) {
			return false; // not found
		}
	}
	return true;
}

// Modified
vector<string> QueryPreprocessor::createResultsClause(string query) {
	vector<string> clause;
	regex resultSyntax(RESULT_REGEX);
	smatch matches;
	regex_search(query, matches, resultSyntax);
	string aliasType = entityAliases[matches[1].str()];
	string aliasName = matches[1].str();
	clause.push_back(aliasName); // Added
	//clause = { aliasType, aliasName }; 
	return clause;
}

// Added
SUCH_THAT_CLAUSE QueryPreprocessor::createSuchThatClause(string relationship, string param1, string param2) {
	SUCH_THAT_CLAUSE clause;
	regex transSyntax(TRANS_REGEX);
	smatch matches;
	bool hasTransitiveClosure = false;
	if (regex_search(relationship, matches, transSyntax)) {
		hasTransitiveClosure = true;
	}
	bool paramIsSynonym1 = isSynonym(param1);
	bool paramIsSynonym2 = isSynonym(param2);
	clause = { stripDoubleQuotes(param1), stripDoubleQuotes(param2),
		hasTransitiveClosure, paramIsSynonym1, paramIsSynonym2 };
	return clause;
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

	if (!paramValid1) cout << endl << endl << "### 1st parameter in " << relationship << " relationship is invalid";
	if (!paramValid2) cout << endl << endl << "### 2nd parameter in " << relationship << " relationship is invalid";

	return paramValid1 && paramValid2;
}

string QueryPreprocessor::getParameterType(string param) {
	if (Utility::isInteger(param)) {
		return keywords::query::STMT_VAR;
	}
	regex doubleQuotes("[\"].*[\"]");
	if (regex_match(param, doubleQuotes)) {
		return "_NAME";
	}
	if (isSynonym(param)) {
		return entityAliases[param];
	}
	return "";
}

bool QueryPreprocessor::isSynonym(string param) {
	if (entityAliases.count(param) == 1) {
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
