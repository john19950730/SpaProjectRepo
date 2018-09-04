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
	static int addVariable(string varName);
	static void newProgram(string progName);
	static void newProcedure(string procName);
	static void addAssignment(string variableName, int immediate);

	static bool setModifies(int stmtNo, string varName);

	static bool isFollows(int stmtNo1, int stmtNo2);
	static bool isModifies(int stmtNo1, string varName);

	static int * getAssignmentStmts();
};
