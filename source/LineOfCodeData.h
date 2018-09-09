#pragma once


#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class LineOfCodeData {
public:
	int store(string type, string actualData
		, std::stack <std::string> nestlevel);

private:
	string typeOfData; //whether procedure, read, print, while, if, assign...
	string actualData; // the actual line of code
	std::stack <std::string> nesting_level; // pops out the parent of this element and subsequent parents

};
