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
	static int CodeParser::checkFollows();
private:
	static vector<LineOfCodeData> CodeParser::lineData;
	static stack <string> CodeParser::nesting_level; //save curr nesting level at this line of code
};