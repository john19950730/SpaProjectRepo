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

QueryObject* QueryPreprocessor::getQueryObject() {
	return this->queryObject;
}

bool QueryPreprocessor::parseQuery(string query)
{
	if (!isValidQuery(query)) {
		cout << endl << "##### Query syntax not valid!" << endl;
		return false;
	}
	
	extractAliasesFromDeclaration(query);

	if (!buildQueryObject(query)) {
		cout << endl << "##### Query not valid!" << endl;
		return false;
	}

	// [SOLVED] doesn't print/access properly (only for select clause)
	/*cout << "Testing parsing: " << endl;
	SELECT_VAR_CLAUSE selectClause = queryObject->getSelectClause();
	cout << "Variable name: " << selectClause.variableName << endl;*/
	// cout << queryObject->getSelectClause()->variableName << endl;

	return true;
}

bool QueryPreprocessor::buildQueryObject(string query) {
	if (!isValidResultsClause(query))
		return false;
	vector<string> resultsClause = createResultsClause(query);
	queryObject->setSelectClause(resultsClause);

	regex relSyntax(REL_REGEX);
	smatch matches;
	while (regex_search(query, matches, relSyntax)){
		string relationship = matches[1];
		string param1 = matches[2];
		string param2 = matches[3];
		if (isRelationshipParamsValid(relationship, param1, param2)) {
			if (relationship == "Uses" || relationship == "Uses*") {
				vector<SUCH_THAT_CLAUSE> usesClauses; // Added
				SUCH_THAT_CLAUSE usesClause = createSuchThatClause(relationship, param1, param2); // Modified
				usesClauses.push_back(usesClause); // Added
				queryObject->setUsesClause(usesClauses); // Modified
			}
			else if (relationship == "Modifies" || relationship == "Modifies*") {
				vector<SUCH_THAT_CLAUSE> modifiesClauses; // Added
				SUCH_THAT_CLAUSE modifiesClause = createSuchThatClause(relationship, param1, param2); // Modified
				modifiesClauses.push_back(modifiesClause); // Added
				queryObject->setModifiesClause(modifiesClauses); // Modified
			}
			else if (relationship == "Follows" || relationship == "Follows*") {
				vector<SUCH_THAT_CLAUSE> followsClauses; // Added
				SUCH_THAT_CLAUSE followsClause = createSuchThatClause(relationship, param1, param2); // Modified
				followsClauses.push_back(followsClause); // Added
				queryObject->setFollowsClause(followsClauses); // Modified
			}
			else if (relationship == "Parent" || relationship == "Parent*") {
				vector<SUCH_THAT_CLAUSE> parentClauses; // Added
				SUCH_THAT_CLAUSE parentClause = createSuchThatClause(relationship, param1, param2); // Modified
				parentClauses.push_back(parentClause); // Added
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
	clause = { param1, param2, hasTransitiveClosure, false, false }; // Please determine if params are synonyms
	return clause;
}

/*STMT_PROC_VAR_RS_CLAUSE QueryPreprocessor::createStmtProcVarRsClause(string relationship, string param1, string param2) {
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
	clause = { param1, param2, hasTransitiveClosure };
	return clause;
}*/

bool QueryPreprocessor::isRelationshipParamsValid(string relationship, string param1, string param2) {
	string paramType1 = getParameterType(param1);
	string paramType2 = getParameterType(param2);
	cout << "param1: " << param1 << endl;
	cout << "param2: " << param2 << endl;
	cout << "paramType1: " << paramType1 << endl;
	cout << "paramType2: " << paramType2 << endl;
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

	cout << "paramValid1: " << paramValid1 << endl;
	cout << "paramValid2: " << paramValid2 << endl;

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

