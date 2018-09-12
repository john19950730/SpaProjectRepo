#include "QueryPreprocessor.h"
#include "QueryObject.h"
#include "Utility.h"
#include "Keywords.h"

QueryPreprocessor::QueryPreprocessor()
{
	synonymTable = {};
	relParamTypes = {};
	queryObject = new QueryObject();

	vector<string> usesModParam1 = { keywords::query::STMT_VAR, keywords::query::PROC_VAR, "_NAME" };
	vector<string> usesModParam2 = { keywords::query::VARIABLE_VAR, "_", "_NAME" };
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
	if (!isValidQuerySyntax(query)) {
		cout << endl << endl << "##### Query syntax is invalid!" << endl;
		cout << endl << "### Example usage:  variable v; procedure v; select v such that Uses(1, v)" << endl;
		cout << "#### keywords are case-sensitive i.e. relationships must begin with an upper-case letter, but 'select' and 'Select' are both accepted" << endl;
		cout << "#### semicolon at the end of `select` clause is optional" << endl << endl;
		return false;
	}
	
	extractSynonymsFromDeclaration(query);

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

	vector<SUCH_THAT_CLAUSE> usesClauses;
	vector<SUCH_THAT_CLAUSE> modifiesClauses;
	vector<SUCH_THAT_CLAUSE> followsClauses;
	vector<SUCH_THAT_CLAUSE> parentClauses;

	regex relSyntax(REL_REGEX);
	smatch matches;
	while (regex_search(query, matches, relSyntax)){
		string relationship = matches[1];
		string param1 = matches[2];
		string param2 = matches[3];
		SUCH_THAT_CLAUSE clause;
		if (isRelationshipParamsValid(relationship, param1, param2)) {
			if (relationship == "Uses" || relationship == "Uses*") {
				clause = createSuchThatClause(relationship, param1, param2);
				usesClauses.push_back(clause);
				queryObject->setUsesClause(usesClauses);
			}
			else if (relationship == "Modifies" || relationship == "Modifies*") {
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

// Checks if query syntax is valid
bool QueryPreprocessor::isValidQuerySyntax(string query) {	
	regex querySyntax(QUERY_SYNTAX_REGEX);
	return regex_match(query, querySyntax);
}

bool QueryPreprocessor::extractSynonymsFromDeclaration(string query) {
	regex declarationSyntax(DECL_REGEX);
	smatch matches;

	while (regex_search(query, matches, declarationSyntax)) {
		string designEntity = matches[1];
		string synonymStr = matches[2];
		vector<string> synVctr = Utility::splitByDelimiter(synonymStr, ",");
		for (size_t i = 0; i < synVctr.size(); i++)
		{
			synonymTable[synVctr[i]] = designEntity;
		}
		query = matches.suffix();
	}

	return true;
}

bool QueryPreprocessor::isValidResultsClause(string query) {
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
	if (param == "_") {
		return "_";
	}
	regex doubleQuotes("[\"].*[\"]");
	if (regex_match(param, doubleQuotes)) {
		return "_NAME";
	}
	if (isSynonym(param)) {
		return synonymTable[param];
	}
	return "";
}

bool QueryPreprocessor::isSynonym(string param) {
	if (synonymTable.count(param) == 1) {
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
