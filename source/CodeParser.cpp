#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <stack>
#include <algorithm>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "CodeParser.h"
#include "LineOfCodeData.h"
#include "Keywords.h"

stack <string> CodeParser::nesting_level;
vector<LineOfCodeData> CodeParser::lineData;

int CodeParser::parse(string code) {
	int start = 0;
	int lineCount = 1;
	static vector<string> line; //saves line of code 


	for (int i = 0; i < code.length(); i++) { //logic for read code line by line
		if (code[i] == '\n') { // encounter a nextline
			int length = i + 1; 
			std::string subString = code.substr(start, length - start);
			processLine(subString,lineCount);//process this line
			line.push_back(subString); //save into vector
			std::cout << lineCount << " line is: " << line.at(lineCount-1);
			lineCount++;
			start = length;
		}
	}

	std::cout << lineData.size();

	return 0;
}

int CodeParser::processLine(string lineOfCode, int lineNum) {

	std::regex equals_regex("={1,1}");
	std::regex close_regex("\\}");
	std::regex procedure_regex("procedure");
	std::regex while_regex("while"); //take note of nesting lvl
	std::regex if_regex("if"); //take note of nesting lvl
	std::regex then_regex("then");
	std::regex else_regex("else");
	std::regex read_regex("read");
	std::regex print_regex("print");

	//search line of code
	int foundProcedure = std::regex_search(lineOfCode, procedure_regex);
	int foundWhile = std::regex_search(lineOfCode, while_regex);
	int foundIf = std::regex_search(lineOfCode, if_regex);
	int foundThen = std::regex_search(lineOfCode, then_regex);
	int foundElse = std::regex_search(lineOfCode, else_regex);
	int foundRead = std::regex_search(lineOfCode, read_regex);
	int foundPrint = std::regex_search(lineOfCode, print_regex);

	int foundClose = std::regex_search(lineOfCode, close_regex); //finds close bracket, means nesting level has ended

	int foundEquals = std::regex_search(lineOfCode, equals_regex);

	//need to check for follows
	//need to check for parents
	//currprocedure,prevprocedure, ignore main procedure
	//currstatement,prevstatment

	if (foundProcedure == 1) {
		//procedure found
		std::cout << "Procedure Found!!!!";
		CodeParser::nesting_level.push("procedure");
	}
	if (foundWhile == 1) {
		//while found
		std::cout << "While Found!!!!";
		CodeParser::nesting_level.push("while");
		LineOfCodeData lcd;
		lcd.store("while", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector

	}
	if (foundIf == 1 && foundThen == 1) {
		//if found
		std::cout << "If Found!!!!";
		CodeParser::nesting_level.push("if");
		LineOfCodeData lcd;
		lcd.store("if", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
	}
	if (foundClose == 1) {
		//close bracket found
		std::cout << "Close Found!!!!";
		std::cout << "end of nesting for: " << CodeParser::nesting_level.top();
		CodeParser::nesting_level.pop();
	}
	if (foundElse == 1) {
		//else found
		std::cout << "Else Found!!!!";
		CodeParser::nesting_level.push("else");
	}
	if (foundRead == 1) {
		//read found
		std::cout << "Read Found!!!!";
		LineOfCodeData lcd;
		lcd.store("read", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
	}
	if (foundPrint == 1) {
		//print found
		std::cout << "Print Found!!!!";
		LineOfCodeData lcd;
		lcd.store("print", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
	}
	if (foundProcedure != 1 && foundWhile != 1 && foundIf != 1 && foundThen != 1 && foundElse != 1
		&& foundRead != 1 && foundPrint != 1 && foundEquals == 1) {
		//assignment
		std::cout << "Assignment Found!!!!";
		LineOfCodeData lcd;
		lcd.store("assignment", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
	}

	return 0;
}

string CodeParser::tokenize(string keyword, string line) {
	std::regex patternP(keyword);
	string token = std::regex_replace(line, patternP, "");
	token.erase(std::remove(token.begin(), token.end(), '{'), token.end());
	token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
	return token;
}

int CodeParser::checkFollows() {

	return 0;
}

