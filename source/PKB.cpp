#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"

static vector<string> varList;
static int varListIndex = 0;
static vector<int> assignList;
static int assignListIndex = 0;

static TNode<int> **followsList;
static vector< vector<bool> > followsStarTable;
static TNode<int> **parentList;
static vector< vector<bool> > parentTable;


int PKB::addVariable(string varName)
{
	varList.push_back(varName);
	return varListIndex++;
}

int PKB::addAssign(int stmtNo)
{
	assignList.push_back(stmtNo);
	return assignListIndex++;
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

bool PKB::isFollows(int stmtNo1, int stmtNo2, bool star)
{
	return false;
}

bool PKB::isParent(int stmtNo1, int stmtNo2, bool star)
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

vector<string> PKB::getVariables()
{
	return varList;
}

vector<int> PKB::getAssigns()
{
	return assignList;
}
