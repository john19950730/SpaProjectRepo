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
	static VarTable* varTable; 
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);

	static int addVariable(string varName, VarTable *varTable);
	static int newProgram(string progName);
	static int newProcedure(string procName);
	static int addAssignment(string procName);

	static bool setModifies(int stmtNo, string varName);

	static bool isFollows(int stmtNo1, int stmtNo2);
	static bool isModifies(int stmtNo1, string varName);

	static int * getAssignmentStmts();
};
