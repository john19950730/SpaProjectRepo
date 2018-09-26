#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "LineOfCodeData.h"
#include "Keywords.h"
#include <regex>
#include <stack>
#include <utility>

int LineOfCodeData::store(string type, string aData
	, std::stack <std::pair<int, string>> nestlevel) {

	typeOfData = type;
	actualData = aData;
	nesting_level = nestlevel;

	return 0;
}

std::stack <std::pair<int, string>> LineOfCodeData::getNestingLevel() {
	return nesting_level;
}
