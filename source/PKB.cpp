#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#include "PKB.h"
#include "TNode.h"

static vector<string> varList;
static int varListIndex = 0;
static vector<int> assignList;
static int assignListIndex = 0;

// element at index i means Follows(i, element) holds
static vector<int> followsList;
static vector< vector<bool> > followsStarTable;

// element at index i means Parent(element, i) holds
static vector<int> parentList;
static vector< vector<bool> > parentStarTable;


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
	//TODO: implementation for storing follows* relation
	followsList[stmtBefore] = stmtAfter;
}

void PKB::addParent(int stmtParent, int stmtChild)
{
	//TODO: implementation for storing parent* relation
	parentList[stmtChild] = stmtParent;
}

void PKB::addUses(int stmtNo, string varName)
{
}

void PKB::addModifies(int stmtNo, string varName)
{

}

bool PKB::isFollows(int stmtNo1, int stmtNo2, bool star)
{
	if (!star) {
		return followsList[stmtNo1] == stmtNo2;
	}
	else {
		return followsStarTable[stmtNo1][stmtNo2];
	}
}

bool PKB::isParent(int stmtNo1, int stmtNo2, bool star)
{
	if (!star) {
		return parentList[stmtNo2] == stmtNo1;
	}
	else {
		return parentStarTable[stmtNo1][stmtNo2];
	}
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
