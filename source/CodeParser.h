#pragma once


#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "LineOfCodeData.h"

using namespace std;
class LineOfCodeData;

class CodeParser {
public:
	static int parse(string);
	static int CodeParser::processLine(string lineOfCode, int lineNum);
	static string CodeParser::tokenize(string keyword, string line);
	static int CodeParser::checkFollows(); //return statement before
	static string CodeParser::checkModifies(string stmtType, string stmt); //return var being modified
private:
	static vector<LineOfCodeData> CodeParser::lineData;
	static int CodeParser::lineNumber;
	static stack <string> CodeParser::nesting_level; //save curr nesting level at this line of code
};