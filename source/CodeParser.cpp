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
int CodeParser::lineNumber = 0;

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

	if (foundProcedure == 1) {
		CodeParser::nesting_level.push("procedure");
	}
	if (foundWhile == 1) {
		CodeParser::nesting_level.push("while");
		LineOfCodeData lcd;
		lcd.store("while", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
	}
	if (foundIf == 1 && foundThen == 1) {
		CodeParser::nesting_level.push("if");
		LineOfCodeData lcd;
		lcd.store("if", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
	}
	if (foundClose == 1) {
		CodeParser::nesting_level.pop();
	}
	if (foundElse == 1) {
		CodeParser::nesting_level.push("else");
	}
	if (foundRead == 1) {
		LineOfCodeData lcd;
		lcd.store("read", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		//chiying api
		PKB::addModifies(lineNumber,checkModifies("read",lineOfCode));
	}
	if (foundPrint == 1) {
		LineOfCodeData lcd;
		lcd.store("print", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		// add uses
	}
	if (foundProcedure != 1 && foundWhile != 1 && foundIf != 1 && foundThen != 1 && foundElse != 1
		&& foundRead != 1 && foundPrint != 1 && foundEquals == 1) {
		LineOfCodeData lcd;
		lcd.store("assignment", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		//find var being modified
		PKB::addModifies(lineNumber,checkModifies("assignment", lineOfCode));
	}

	return 0;
}

string CodeParser::tokenize(string keyword, string line) {
	std::regex pattern(keyword);
	string token = std::regex_replace(line, pattern, "");
	token.erase(std::remove(token.begin(), token.end(), '{'), token.end());
	token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
	return token;
}

int CodeParser::checkFollows() {

	return 0;
}

string CodeParser::checkModifies(string stmtType, string stmt) { //returns var being modified

	string token = "";
	if (stmtType == "read") {
		std::regex pattern(stmtType);
		token = std::regex_replace(stmt, pattern, "");
		token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
		token.erase(std::remove(token.begin(), token.end(), '\t'), token.end());//remove tab
		token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());//remove nextline
		token.erase(std::remove(token.begin(), token.end(), ';'), token.end());
	}
	if (stmtType == "assignment") {
		for (char& c : stmt) {
			if (c != '=') {
				token += c;
				
			}
			else {
				break;
			}
		}
		token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
	}

	return token;
}

