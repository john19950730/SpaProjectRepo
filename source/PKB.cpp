#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
// element at index i, j means Follows*(i, j) holds
static vector< vector<bool> > followsStarTable;

// element at index i means Parent(element, i) holds
static vector<int> parentList;
// element at index i, j means Parent*(i, j) holds
static vector< vector<bool> > parentStarTable;

// array at index i of usesTable[i] contains list of variables v where Uses(i, v) holds
static vector< vector<string> > usesTable;

// array at index i of modifiesTable[i] contains list of variables v where Modifies(i, v) holds
static vector< vector<string> > modifiesTable;

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
	followsList[stmtBefore] = stmtAfter;

	followsStarTable[stmtBefore][stmtAfter] = true;
	followsStarTable[stmtBefore][stmtBefore] = false;
	followsStarTable[stmtAfter][stmtAfter] = false;
	
	int i;
	for (i = 1; i <= stmtBefore; ++i) {
		followsStarTable[i][stmtAfter] = followsStarTable[i][stmtBefore];
	}
	for (i = stmtAfter + 1; i <= followsStarTable[stmtBefore].size(); ++i) {
		followsStarTable[stmtBefore][i] = followsStarTable[stmtBefore][i];
	}
}

void PKB::addParent(int stmtParent, int stmtChild)
{
	parentList[stmtChild] = stmtParent;

	parentStarTable[stmtParent][stmtChild] = true;
	parentStarTable[stmtParent][stmtParent] = false;
	parentStarTable[stmtChild][stmtChild] = false;

	int parent = stmtParent;
	while (parentList[parent]) {
		parentStarTable[parent][stmtChild] = true;
	}
}

void PKB::addUses(int stmtNo, string varName)
{
	usesTable[stmtNo].push_back(varName);
}

void PKB::addModifies(int stmtNo, string varName)
{
	modifiesTable[stmtNo].push_back(varName);
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
	return find(usesTable[stmtNo1].begin(), usesTable[stmtNo1].end(), varName) != usesTable[stmtNo1].end();
}

bool PKB::isModifies(int stmtNo1, string varName)
{
	return find(modifiesTable[stmtNo1].begin(), modifiesTable[stmtNo1].end(), varName) != modifiesTable[stmtNo1].end();
}

vector<int> PKB::getAllStmtThatUses(string v)
{
	return vector<int>();
}

vector<int> PKB::getAllAssignmentThatUses(string v)
{
	return vector<int>();
}

vector<int> PKB::getAllStmtThatModifies(string v)
{
	return vector<int>();
}

vector<int> PKB::getAllAssignmentThatModifies(string v)
{
	return vector<int>();
}

vector<string> PKB::getVariables()
{
	return varList;
}

vector<int> PKB::getAssigns()
{
	return assignList;
}
