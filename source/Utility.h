#pragma once

#include <string>
#include <vector>
#include <regex>
#include <algorithm> 
#include <cctype>
#include <locale>
#include <sstream>
#include <stack>
#include <limits>

using namespace std;

class Utility {
public:
	static bool isValidVariableName(string s);
	static bool isInteger(string s);
	static bool isUnderscore(string s);

	static vector<string> splitByDelimiter(string s, string delimiter);
	static vector<string> splitByRegex(string s, regex delimiters);

	static string convertInfixToPostfix(string infixExpression);
	static int priority(char a);
	static bool validateInfixExpression(string expression);

	static void ltrim(string &s);
	static void rtrim(std::string &s);
	static string trim_copy(string s);
};