#include <algorithm> 
#include <cctype>
#include <locale>

#include "QueryPreprocessor.h"

bool QueryPreprocessor::parseQuery(string query)
{
	vector<string> querySubstatements = splitByDelimiter(query, ";");
	return false;
}

bool QueryPreprocessor::buildQueryObject(vector<string> querySubstatements) {	
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