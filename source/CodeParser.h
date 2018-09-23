#pragma once


#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "LineOfCodeData.h"

using namespace std;
class LineOfCodeData;

class CodeParser {
public:
	static int parse(string);
	static int CodeParser::processLine(string lineOfCode, int lineNum);
	static int CodeParser::checkFollows(int lineNumber); //return statement before
	static string CodeParser::checkModifies(string stmtType, string stmt); //return var being modified
	static std::vector<std::string> CodeParser::checkUses(string stmtType, string stmt);
	static int CodeParser::checkForNestingModifies(string stmtType, string stmt);
	static int CodeParser::checkForNestingUses(std::vector<std::string> vars);
	static std::vector<std::string> CodeParser::split(string s);
	static std::vector<std::string> CodeParser::splitWhileIfConditions(string s);
	static bool is_number(string s);
	static bool is_duplicate(string s, std::vector<std::string> list);
	static bool CodeParser::is_appeared(char c, string s);
	static bool CodeParser::compare_nesting(std::stack <std::pair<int, string>> prevNestingLevel, std::stack <std::pair<int, string>> currNestingLevel);
	static int CodeParser::checkParent(int lineNumber);
private:
	static vector<LineOfCodeData> CodeParser::lineData;
	static int CodeParser::lineNumber;
	static int CodeParser::prevLineNumber;
	static int CodeParser::prevNestingLevel;
	static stack <std::pair<int, string>> CodeParser::nesting_level; //save curr nesting level at this line of code
};