#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "CodeParser.h"
#include "Keywords.h"

int CodeParser::parse(string code) {
	int start = 0;
	int lineCount = 0;
	std::vector<std::string> line;

	for (int i = 0; i < code.length(); i++) { //logic for read code line by line
		if (code[i] == '\n') { // encounter a nextline
			int length = i + 1; 
			std::string subString = code.substr(start, length - start);
			processLine(subString);//process this line
			line.push_back(subString); //save into vector
			std::cout << lineCount + 1 << " line is: " << line.at(lineCount);
			lineCount++;
			start = length;
		}
	}

	return 0;
}

int CodeParser::processLine(string lineOfCode) {
	//determine if it is a procedure
	if (lineOfCode.find(keywords::PROCEDURE) != -1) {
		std::cout << "Procedure Found!!!!";
	}
	//determine if it is an assignment
	if (lineOfCode.find(keywords::ASSIGNMENT) != -1) {
		std::cout << "Assignment Found!!!!";
		//save node,
		//save line number, type: assignment
		//save variable being assigned (left child)
		//save value being passed (right child)
		//chi ying api here?
	}
	return 0;
}
