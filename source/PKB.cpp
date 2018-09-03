#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"

static int varTableIndex = 0;

int PKB::setProcToAST(PROC p, TNode* r) {
	return NULL;
}

TNode* PKB::getRootAST (PROC p){
	return NULL;
}

int PKB::addVariable(string varName, VarTable *varTable)
{
	varTable[varTableIndex] = varName;
	return ++varTableIndex;
}

int PKB::newProgram(string progName)
{
	return 0;
}

int PKB::newProcedure(string procName)
{
	return 0;
}

int PKB::addAssignment(string procName)
{
	return 0;
}

bool PKB::setModifies(int stmtNo, string varName)
{
	return false;
}

bool PKB::isFollows(int stmtNo1, int stmtNo2)
{
	return false;
}

bool PKB::isModifies(int stmtNo1, string varName)
{
	return false;
}

int * PKB::getAssignmentStmts()
{
	return 0;
}
