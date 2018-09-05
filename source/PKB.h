#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef short PROC;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
public:
	// SPA relationships table
	static void addFollows(int stmtBefore, int stmtAfter);
	static void addParent(int stmtParent, int stmtChild);
	static void addUses(int stmtNo, string varName);
	static void addModifies(int stmtNo, string varName);

	// SPA synonyms table
	static int addVariable(string varName);
	static int addAssign(string variableName);

	// SPA relationships query
	static bool isFollows(int stmtNo1, int stmtNo2);
	static bool isParent(int stmtNo1, int stmtNo2);
	static bool isUses(int stmtNo1, string varName);
	static bool isModifies(int stmtNo1, string varName);
	
	// SPA synonyms query
	static string * getVariables();
	static int * getAssigns();
};
