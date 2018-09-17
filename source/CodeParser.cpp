#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <stack>
#include <algorithm>
#include <utility>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "CodeParser.h"
#include "LineOfCodeData.h"
#include "Keywords.h"

stack < std::pair<int,string> > CodeParser::nesting_level;
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
	//std::cout << nesting_level.size();

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
		CodeParser::nesting_level.push(make_pair(lineNumber,"procedure"));
		//save procedure name here
	}
	if (foundWhile == 1) {
		LineOfCodeData lcd;
		lcd.store("while", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		CodeParser::nesting_level.push(make_pair(lineNumber, "while"));
		//find var being used
		std::vector<std::string> variables = checkUses("while", lineOfCode);
		for (int i = 0; i < variables.size(); i++) { //for every variable being used
			PKB::addUses(lineNumber, variables.at(i));
		}
		//check if being used in parent nesting
		checkForNestingUses(variables);
	}
	if (foundIf == 1 && foundThen == 1) {
		LineOfCodeData lcd;
		lcd.store("if", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		CodeParser::nesting_level.push(make_pair(lineNumber, "if"));
		//find var being used
		std::vector<std::string> variables = checkUses("if", lineOfCode);
		for (int i = 0; i < variables.size(); i++) { //for every variable being used
			PKB::addUses(lineNumber, variables.at(i));
		}
		//check if being used in parent nesting
		checkForNestingUses(variables);
	}
	if (foundClose == 1 && foundElse != 1) {
		CodeParser::nesting_level.pop();
	}
	if (foundRead == 1) {
		LineOfCodeData lcd;
		lcd.store("read", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		//find var being modified
		PKB::addModifies(lineNumber,checkModifies("read",lineOfCode));
		//check if being modifies in parent nesting
		checkForNestingModifies("read", lineOfCode);
	}
	if (foundPrint == 1) {
		LineOfCodeData lcd;
		lcd.store("print", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		//find var being used
		std::vector<std::string> variables = checkUses("print", lineOfCode);
		PKB::addUses(lineNumber, variables.at(0)); //only one variable
		//check if being used in parent nesting
		checkForNestingUses(variables);
	}
	if (foundProcedure != 1 && foundWhile != 1 && foundIf != 1 && foundThen != 1 && foundElse != 1
		&& foundRead != 1 && foundPrint != 1 && foundEquals == 1) {
		LineOfCodeData lcd;
		lcd.store("assignment", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		//find var being modified
		PKB::addModifies(lineNumber,checkModifies("assignment", lineOfCode));
		std::cout << "check uses: ";
		//find var being used
		std::vector<std::string> variables = checkUses("assignment", lineOfCode);
		for (int i = 0; i < variables.size(); i++) { //for every variable being used
			PKB::addUses(lineNumber, variables.at(i));
		}
		//check if being used/modifies in parent nesting
		checkForNestingModifies("assignment", lineOfCode);
		checkForNestingUses(variables);
	}

	return 0;
}

int CodeParser::checkFollows() {

	return 0;
}

std::vector<std::string> CodeParser::checkUses(string stmtType, string stmt) { //returns var being modified

	std::vector<std::string> vars;
	string token = "";
	if (stmtType == "while") {
		std::regex pattern(stmtType); // pattern= "while"
		token = std::regex_replace(stmt, pattern, ""); //removes "while from the stmt"
		token.erase(std::remove(token.begin(), token.end(), ' '), token.end()); //removes space
		token.erase(std::remove(token.begin(), token.end(), '\t'), token.end());//remove tab
		token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());//remove nextline
		token.erase(std::remove(token.begin(), token.end(), ';'), token.end());
		vars = splitWhileIfConditions(token);
	}
	if (stmtType == "if") {
		std::regex pattern(stmtType); // pattern= "if"
		token = std::regex_replace(stmt, pattern, ""); //removes "if from the stmt"
		token.erase(std::remove(token.begin(), token.end(), ' '), token.end()); //removes space
		token.erase(std::remove(token.begin(), token.end(), '\t'), token.end());//remove tab
		token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());//remove nextline
		token.erase(std::remove(token.begin(), token.end(), ';'), token.end());
		vars = splitWhileIfConditions(token);
	}
	if (stmtType == "print") {
		std::regex pattern(stmtType);
		token = std::regex_replace(stmt, pattern, "");
		token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
		token.erase(std::remove(token.begin(), token.end(), '\t'), token.end());//remove tab
		token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());//remove nextline
		token.erase(std::remove(token.begin(), token.end(), ';'), token.end());
		vars.push_back(token);
	}
	if (stmtType == "assignment") {
		token = stmt;
		for (char& c : stmt) {
			if (c != '=') {
				token.erase(0, 1);
				
			}
			else {
				token.erase(0, 1);
				break;
			}
		}
		token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
		token.erase(std::remove(token.begin(), token.end(), '\t'), token.end());//remove tab
		token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());//remove nextline
		token.erase(std::remove(token.begin(), token.end(), '('), token.end());//TODO: handle brackets sometime later
		token.erase(std::remove(token.begin(), token.end(), ')'), token.end());//TODO: handle brackets sometime later
		vars = split(token);
	}

	return vars;
}

std::vector<std::string> CodeParser::splitWhileIfConditions(string s) {
	std::vector<std::string> splitted;
	string delim = "*+-/%!=&|<>()";
	string unbrokenString = "";
	char nextChar = ' ';
	for (int i = 0; i < s.length(); i++) {
		if(i != s.length()-1){ //not the last character
			nextChar = s.at(i + 1);
		}
		else {
			nextChar = ' '; //no last character end of string
		}
		if (!is_appeared(s.at(i), delim)) { // if curr char position is NOT a delim
			//its a character
			unbrokenString += s.at(i);
				if (is_appeared(nextChar, delim)) { //if my next char is a delim
					//save variable so far
					if (!is_number(unbrokenString)) { //not a num
						if (!is_duplicate(unbrokenString, splitted)) { //not a duplicate in vector
							//add it into splitted
							splitted.push_back(unbrokenString);
						}
					}
					unbrokenString = "";//reset temp
				}
		}
			
	}


	return splitted;
}

bool CodeParser::is_appeared(char c, string s) { //if c appears in cA, return true
	for (int i = 0; i < s.length(); i++) {
		if (c == s.at(i)) {
			return true;
		}
	}
	return false;
}

std::vector<std::string> CodeParser::split(string s) {
	//split a string e.g. cenX+x+1*y/x;
	//eliminate duplicate variables
	//eliminate int constants
	std::vector<std::string> splitted;
	string delim = "*+-/%;";

	string temp = "";
		for (char& c : s) {
				if (!is_appeared(c,delim)) { //if curr character is not a delim
					temp += c;
				}
				else { //delimiter encountered
					//save token so far
					if (!is_number(temp)) { //not a num
						if (!is_duplicate(temp, splitted)) { //not a duplicate in vector
							//add it into splitted
							splitted.push_back(temp);
						}
					}
					temp = "";//reset temp
				}
		}

	return splitted;
}

bool CodeParser::is_duplicate(string s, std::vector<std::string> list) {
	for (int i = 0; i < list.size(); i++) {
		if (s == list.at(i)) {
			//found a duplicate element
			return true;
		}
	}
	return false;
}

bool CodeParser::is_number(string s)
{
	string numbers = "0123456789";
	int numbersIndex = 0;

	for (char& c : s) {
		for (char& n : numbers) {
			if (c == n) {
				//this c is a number
				numbersIndex++;
			}
		}
	}
	if (numbersIndex == s.length()) { //if every char was a digit
		return true;
	}
	else {
		return false;
	}

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

int CodeParser::checkForNestingModifies(string stmtType, string stmt) {
	if (nesting_level.size() > 1) { //nesting level greater than 2, first element in stack is procedure
		stack < std::pair<int, string> > curr_nesting_level = nesting_level;
		while (curr_nesting_level.size() != 1) { //the if/while statement also modifies this variable
			std::pair<int, string> top = curr_nesting_level.top();
			PKB::addModifies(top.first, checkModifies(stmtType, stmt));
			curr_nesting_level.pop();
		}
	}
	return 0;
}

int CodeParser::checkForNestingUses(std::vector<std::string> vars) {
	if (nesting_level.size() > 1) { //nesting level greater than 2, first element in stack is procedure
		stack < std::pair<int, string> > curr_nesting_level = nesting_level;
		while (curr_nesting_level.size() != 1) { //the if/while statement also modifies this variable
			std::pair<int, string> top = curr_nesting_level.top();
			for (int i = 0; i < vars.size(); i++) {
				PKB::addUses(top.first, vars.at(i));
			}
			curr_nesting_level.pop();
		}
	}
	return 0;
}

