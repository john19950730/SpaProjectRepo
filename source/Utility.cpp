# include "Utility.h"
#include "Keywords.h"

bool Utility::isValidVariableName(string s) {
	return regex_match(s, regex("^[a-zA-Z][a-zA-Z0-9]*?$"));
}

bool Utility::isInteger(string s)
{
	return s.find_first_not_of("0123456789") == std::string::npos;
	/*std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();*/
}

bool Utility::matchesDesignEntityKeyword(string s) {
	for (size_t i = 0; i < keywords::query::DESIGN_ENTITY.size(); i++) {
		if (s == keywords::query::DESIGN_ENTITY[i]) {
			return true;
		}
	}
	return false;
}

vector<string> Utility::splitByDelimiter(string s, string delimiter)
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

vector<string> Utility::splitByRegex(string s, regex delimiters)
{
	vector<string> vector = {};
	auto words_begin = sregex_iterator(s.begin(), s.end(), delimiters);
	auto words_end = sregex_iterator();
	for (std::sregex_iterator i = words_begin; i != words_end; ++i)
		vector.push_back((*i).str());
	return vector;
}

// trim from start (in place)
void Utility::ltrim(string &s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
		return !isspace(ch);
	}));
}

// trim from end (in place)
void Utility::rtrim(string &s) {
	s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
		return !isspace(ch);
	}).base(), s.end());
}

// trim from both ends (copying)
string Utility::trim_copy(string s) {
	ltrim(s);
	rtrim(s);
	return s;
}