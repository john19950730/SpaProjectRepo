#include <algorithm> 
#include <cctype>
#include <locale>

#include "QueryPreprocessor.h"
#include "EntityAliasTable.h"

bool QueryPreprocessor::parseQuery(string query)
{
	vector<string> querySubstatements = splitByDelimiter(query, ";");
	buildQueryTree(querySubstatements);
	return false;
}

bool QueryPreprocessor::buildQueryTree(vector<string> querySubstatements) {
	EntityAliasTable entityAliasTable;
	
	for (string substatement : querySubstatements) {
		// further splits query substatements into words
		vector<string> wordsInQuerySubstatement = splitByDelimiter(substatement, " ");
		// insert into entityAliasTable if not a "select" substatement
		// wip - plans to implement a design entity table to refer
		if (wordsInQuerySubstatement.size() >= 2 && wordsInQuerySubstatement[0] != "select")
			entityAliasTable.insertEntityAlias(wordsInQuerySubstatement);
		if (wordsInQuerySubstatement[0] == "select") {
			// build tree
			// iterate through "select" substatement
			vector<string>::iterator it = wordsInQuerySubstatement.begin();
			std::advance(it, 1);
			while (it != wordsInQuerySubstatement.end()) {
				if (entityAliasTable.getEntityTypeFromAlias(*it) != "") { // found
					cout << endl;
					cout << entityAliasTable.getEntityTypeFromAlias(*it) << endl;
				}
				++it;
			}
		}
	}

	// Print table
	/*vector<EntityAliasInfo> table = entityAliasTable.getTableData();
	for (EntityAliasInfo info : table) {
		cout << info.aliasName + ":" + info.entityType << endl;
	}*/
	return false;
}

vector<string> QueryPreprocessor::splitByDelimiter(string s, string delimiter)
{
	size_t pos = 0;
	string token;
	vector<string> vector = {};
	while ((pos = s.find(delimiter)) != string::npos) {
		token = s.substr(0, pos);
		vector.push_back(trim_copy(token));
		s.erase(0, pos + delimiter.length());
	}
	vector.push_back(trim_copy(s));
	return vector;
}

// trim from start (in place)
void QueryPreprocessor::ltrim(string &s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
		return !isspace(ch);
	}));
}

// trim from end (in place)
void QueryPreprocessor::rtrim(string &s) {
	s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
		return !isspace(ch);
	}).base(), s.end());
}

// trim from both ends (copying)
std::string QueryPreprocessor::trim_copy(string s) {
	ltrim(s);
	rtrim(s);
	return s;
}