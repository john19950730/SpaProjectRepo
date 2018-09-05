#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"

static int varTableIndex = 0;
static int varTableCapacity = 100;
static string varTable[100];

int PKB::addVariable(string varName)
{
	*(varTable + varTableIndex) = varName;
	return ++varTableIndex;
}

int PKB::addAssign(string variableName)
{
	return 0;
}

void PKB::addFollows(int stmtBefore, int stmtAfter)
{
}

void PKB::addParent(int stmtParent, int stmtChild)
{
}

void PKB::addUses(int stmtNo, string varName)
{
}

void PKB::addModifies(int stmtNo, string varName)
{

}

bool PKB::isFollows(int stmtNo1, int stmtNo2)
{
	return false;
}

bool PKB::isParent(int stmtNo1, int stmtNo2)
{
	return false;
}

bool PKB::isUses(int stmtNo1, string varName)
{
	return false;
}

bool PKB::isModifies(int stmtNo1, string varName)
{
	return false;
}

string * PKB::getVariables()
{
	return nullptr;
}

int * PKB::getAssigns()
{
	static int dummy[] { 0 } ;
	return dummy;
}
