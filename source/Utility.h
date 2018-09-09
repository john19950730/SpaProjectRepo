#pragma once

#include <string>
#include <vector>
#include <regex>
#include <algorithm> 
#include <cctype>
#include <locale>

using namespace std;

class Utility {
public:
	static bool isValidVariableName(string s);
	static bool matchesDesignEntityKeyword(string s);
	static vector<string> splitByDelimiter(string s, string delimiter);
	static vector<string> splitByRegex(string s, regex delimiters);
	static void ltrim(string &s);
	static void rtrim(std::string &s);
	static string trim_copy(string s);
	static bool isInteger(string str);
};