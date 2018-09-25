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
vector<string> CodeParser::procedures;
pair<int, string> CodeParser::nestingStackElement;
vector<LineOfCodeData> CodeParser::lineData;
int CodeParser::lineNumber = 0;

int CodeParser::parse(string code) {
	int start = 0;
	int lineCount = 1;
	static vector<string> line; //saves line of code
	if (code.at(code.length() - 1) != '\n') { //add nextline at the back of SIMPLE code
		code += '\n';
	}
	for (int i = 0; i < code.length(); i++) { //if encounter a close bracket
		if (code[i] == '}') {
			string firstHalf = code.substr(0, i+1);
			firstHalf += '\n';
			string secondHalf = code.substr(i+1,code.length()-1-i);
			code = firstHalf + secondHalf;
		}
		if (code[i] == '\n') { // encounter a nextline
			int length = i + 1; 
			std::string subString = code.substr(start, length - start);
			processLine(subString);//process this line
			line.push_back(subString); //save into vector
			std::cout << lineCount << " line is: " << line.at(lineCount-1);
			lineCount++;
			start = length;
		}
	}

	std::cout << lineData.size();
	return 0;
}

int CodeParser::processLine(string lineOfCode) {

	std::regex equals_regex("={1,1}");
	std::regex close_regex("\\}");
	std::regex procedure_regex("procedure");
	std::regex while_regex("while");
	std::regex if_regex("if");
	std::regex else_regex("else");
	std::regex read_regex("read");
	std::regex print_regex("print");

	//search line of code
	int foundProcedure = std::regex_search(lineOfCode, procedure_regex);
	int foundWhile = std::regex_search(lineOfCode, while_regex);
	int foundIf = std::regex_search(lineOfCode, if_regex);
	int foundElse = std::regex_search(lineOfCode, else_regex);
	int foundRead = std::regex_search(lineOfCode, read_regex);
	int foundPrint = std::regex_search(lineOfCode, print_regex);
	int foundClose = std::regex_search(lineOfCode, close_regex); //finds close bracket, means nesting level has ended
	int foundEquals = std::regex_search(lineOfCode, equals_regex);

	if (foundProcedure == 1) {
		CodeParser::nesting_level.push(make_pair(lineNumber,"procedure"));//TODO proc always 0 linnenum, parse into PKB add proc
		string procName = extractProcedureName(lineOfCode);
		procedures.push_back(procName);
		PKB::addProcedure(procName); //hardcoded name, start/endline for now!!
	}
	if (foundWhile == 1) {
		LineOfCodeData lcd;
		lcd.store("while", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		PKB::addWhile(lineNumber);
		//find var being used
		std::vector<std::string> variables = checkUses("while", lineOfCode, lineNumber);
		for (int i = 0; i < variables.size(); i++) { //for every variable being used
			PKB::addVariable(variables.at(i));
		}
		for (int i = 0; i < variables.size(); i++) { //for every variable being used
			PKB::addUses(lineNumber, variables.at(i));
			PKB::addProcedureUses(procedures.at(0), variables.at(i));
		}
		//check if being used in parent nesting
		checkForNestingUses(variables);
		checkFollows(lineNumber);
		checkParent(lineNumber, nesting_level);
		CodeParser::nesting_level.push(make_pair(lineNumber, "while"));
	}
	if (foundIf == 1) {
		LineOfCodeData lcd;
		lcd.store("if", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		PKB::addIf(lineNumber);
		//find var being used
		std::vector<std::string> variables = checkUses("if", lineOfCode, lineNumber);
		for (int i = 0; i < variables.size(); i++) { //for every variable being used
			PKB::addVariable(variables.at(i));
		}
		for (int i = 0; i < variables.size(); i++) { //for every variable being used
			PKB::addUses(lineNumber, variables.at(i));
			PKB::addProcedureUses(procedures.at(0), variables.at(i));
		}
		//check if being used in parent nesting
		checkForNestingUses(variables);
		checkFollows(lineNumber);
		checkParent(lineNumber, nesting_level);
		CodeParser::nesting_level.push(make_pair(lineNumber, "if"));
	}
	if (foundElse == 1) { //else encounter
		CodeParser::nesting_level.push(make_pair(0, "else"));
	}
	if (foundRead == 1) {
		LineOfCodeData lcd;
		lcd.store("read", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		PKB::addRead(lineNumber);
		PKB::addVariable(checkModifies("read", lineOfCode));
		//find var being modified
		PKB::addModifies(lineNumber,checkModifies("read",lineOfCode));
		PKB::addProcedureModifies(procedures.at(0), checkModifies("read", lineOfCode)); //TODO: detect procedure
		//check if being modifies in parent nesting
		checkForNestingModifies("read", lineOfCode);
		checkFollows(lineNumber);
		checkParent(lineNumber,nesting_level);
	}
	if (foundPrint == 1) {
		LineOfCodeData lcd;
		lcd.store("print", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		PKB::addPrint(lineNumber);
		//find var being used
		std::vector<std::string> variables = checkUses("print", lineOfCode, lineNumber);
		PKB::addVariable(variables.at(0));
		PKB::addUses(lineNumber, variables.at(0)); //only one variable
		PKB::addProcedureUses(procedures.at(0), variables.at(0));
		//check if being used in parent nesting
		checkForNestingUses(variables);
		checkFollows(lineNumber);
		checkParent(lineNumber,nesting_level);
	}
	if (foundProcedure != 1 && foundWhile != 1 && foundIf != 1 && foundElse != 1
		&& foundRead != 1 && foundPrint != 1 && foundEquals == 1) { //TODO: input validation, detect invalid line: clearPKB(), or when new program loaded
		LineOfCodeData lcd;
		lcd.store("assignment", lineOfCode, nesting_level);
		lineData.push_back(lcd); //add line object into vector
		lineNumber++;
		PKB::addAssign(lineNumber);
		//find var being modified
		//add it to VarTable and Modifies relationship
		PKB::addVariable(checkModifies("assignment", lineOfCode));
		PKB::addModifies(lineNumber,checkModifies("assignment", lineOfCode));
		PKB::addProcedureModifies(procedures.at(0), checkModifies("assignment", lineOfCode)); //TODO: detect procedure
		//find var being used
		std::vector<std::string> variables = checkUses("assignment", lineOfCode, lineNumber);
		for (int i = 0; i < variables.size(); i++) { //for every variable being used
			PKB::addVariable(variables.at(i));
		}
		for (int i = 0; i < variables.size(); i++) { //for every variable being used
			PKB::addUses(lineNumber, variables.at(i)); //add it to uses relationship
			PKB::addProcedureUses(procedures.at(0), variables.at(i));
		}
		//check if being used/modifies in parent nesting
		checkForNestingModifies("assignment", lineOfCode);
		checkForNestingUses(variables);
		checkFollows(lineNumber);
		checkParent(lineNumber,nesting_level);
	}
	if (foundClose == 1) {
		nestingStackElement = nesting_level.top();
		if (nestingStackElement.second != "if") {
			CodeParser::nesting_level.pop();
			if (nestingStackElement.second == "else") {
				nestingStackElement = nesting_level.top();
				CodeParser::nesting_level.pop();
			}
		}
		else {
			nestingStackElement = make_pair(0, "");
		}
	}
	return 0;
}

string CodeParser::extractProcedureName(string s) {
	string token = "";
	std::regex pattern("procedure"); // procedure
	token = std::regex_replace(s, pattern, ""); //removes "while from the stmt"
	token.erase(std::remove(token.begin(), token.end(), ' '), token.end()); //removes space
	token.erase(std::remove(token.begin(), token.end(), '\t'), token.end());//remove tab
	token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());//remove nextline
	token.erase(std::remove(token.begin(), token.end(), ';'), token.end());
	token.erase(std::remove(token.begin(), token.end(), '{'), token.end());
	return token;
}

int CodeParser::checkParent(int lineNumber , stack < std::pair<int, string> >currNestingLevel) {
	while (!currNestingLevel.empty()) { //if 
		pair<int, string> nestingStackElement = currNestingLevel.top();
		currNestingLevel.pop();
		if (nestingStackElement.first != 0) {
			PKB::addParent(nestingStackElement.first, lineNumber);
			return 1;
			break;
		}
	}
	return 0;
}

int CodeParser::checkFollows(int lineNumber) {
	//check procedure for follows (nesting level 1)
	if (lineNumber > 1) { //make sure you're not first line
		std::stack <std::pair<int, string>> prevNestingLevel;
		prevNestingLevel = lineData.at(lineNumber - 2).getNestingLevel();
		std::stack <std::pair<int, string>> currNestingLevel;
		currNestingLevel = nesting_level;
		bool hasNestingChanged = compare_nesting(prevNestingLevel, currNestingLevel); //check if nesting level has changed
		if (!hasNestingChanged) {
			PKB::addFollows(lineNumber - 1, lineNumber); //previous follows curr
			nestingStackElement = make_pair(0, ""); //clear temp nesting stack element
		}
		else { //nesting level has changed
			if (nestingStackElement.first != 0) {
				PKB::addFollows(nestingStackElement.first, lineNumber); //previous nesting block followed by this line
				nestingStackElement = make_pair(0, ""); //clear element
			}

		}
		//account for if else nesting
	}
	else {
		return 0;
	}
	return 0;
}

bool CodeParser::compare_nesting(std::stack <std::pair<int, string>> prevNestingLevel, std::stack <std::pair<int, string>> currNestingLevel) {
	bool isChanged = false;
	if (prevNestingLevel.size() != currNestingLevel.size()) {
		isChanged = true;
	}
	else {
		while (!currNestingLevel.empty() && !prevNestingLevel.empty()) {
			std::pair<int, string> currNestElement = currNestingLevel.top();
				currNestingLevel.pop();
				std::pair<int, string> prevNestElement = prevNestingLevel.top();
				prevNestingLevel.pop();
			if ((currNestElement.first == prevNestElement.first) && (currNestElement.second == prevNestElement.second)) {
				isChanged = false;
			}
			else {
				isChanged = true;
				return isChanged;
			}
		}
	}
	return isChanged;
}


std::vector<std::string> CodeParser::checkUses(string stmtType, string stmt, int lineNum) { //returns var being modified

	std::vector<std::string> vars;
	string token = "";
	if (stmtType == "while") {
		std::regex pattern(stmtType); // pattern= "while"
		token = std::regex_replace(stmt, pattern, ""); //removes "while from the stmt"
		token.erase(std::remove(token.begin(), token.end(), ' '), token.end()); //removes space
		token.erase(std::remove(token.begin(), token.end(), '\t'), token.end());//remove tab
		token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());//remove nextline
		token.erase(std::remove(token.begin(), token.end(), ';'), token.end());
		vars = splitWhileIfConditions(token, lineNum);
	}
	if (stmtType == "if") {
		std::regex pattern(stmtType); // pattern= "if"
		token = std::regex_replace(stmt, pattern, ""); //removes "if from the stmt"
		token.erase(std::remove(token.begin(), token.end(), ' '), token.end()); //removes space
		token.erase(std::remove(token.begin(), token.end(), '\t'), token.end());//remove tab
		token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());//remove nextline
		token.erase(std::remove(token.begin(), token.end(), ';'), token.end());
		vars = splitWhileIfConditions(token, lineNum);
	}
	if (stmtType == "print") {
		std::regex pattern(stmtType);
		token = std::regex_replace(stmt, pattern, "");
		token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
		token.erase(std::remove(token.begin(), token.end(), '\t'), token.end());//remove tab
		token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());//remove nextline
		token.erase(std::remove(token.begin(), token.end(), ';'), token.end());
		if (!is_number(token)) {
			PKB::addConstant(lineNum, token);
		}
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
		vars = split(token, lineNum);
	}

	return vars;
}

std::vector<std::string> CodeParser::splitWhileIfConditions(string s, int lineNum) {
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
					else { //its a number
						PKB::addConstant(lineNum, unbrokenString);
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

std::vector<std::string> CodeParser::split(string s, int lineNum) {
	//split a string e.g. cenX+x+1*y/x;
	//eliminate duplicate variables
	//save constants in PKB::addConstant
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
					else {
						PKB::addConstant(lineNum, temp);
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
			//TODO: if encounter else, make else point to if
			PKB::addModifies(top.first, checkModifies(stmtType, stmt));
			curr_nesting_level.pop();
		}
	}
	return 0;
}

int CodeParser::checkForNestingUses(std::vector<std::string> vars) {
	if (nesting_level.size() > 1) { //nesting level greater than 2, first element in stack is procedure
		stack < std::pair<int, string> > curr_nesting_level = nesting_level; //TODO: might wanna safely copy stack
		while (curr_nesting_level.size() != 1) { //the if/while statement also modifies this variable
			std::pair<int, string> top = curr_nesting_level.top();
			//TODO: if encounter else, make else point to if
			for (int i = 0; i < vars.size(); i++) {
				PKB::addUses(top.first, vars.at(i));
			}
			curr_nesting_level.pop();
		}
	}
	return 0;
}

