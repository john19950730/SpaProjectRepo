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
static vector<int> readList;
static int readListIndex = 0;
static vector<int> printList;
static int printListIndex = 0;
static vector<int> ifList;
static int ifListIndex = 0;
static vector<int> whileList;
static int whileListIndex = 0;
static vector< pair<string, pair<int, int> > > procedureList;
static int procedureListIndex = 0;

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

int PKB::addRead(int stmtNo)
{
	readList.push_back(stmtNo);
	return readListIndex++;
}

int PKB::addPrint(int stmtNo)
{
	printList.push_back(stmtNo);
	return printListIndex++;
}

int PKB::addIf(int stmtNo)
{
	ifList.push_back(stmtNo);
	return ifListIndex++;
}

int PKB::addWhile(int stmtNo)
{
	whileList.push_back(stmtNo);
	return whileListIndex++;
}

int PKB::addProcedure(string procName, pair<int, int> startEndLine)
{
	procedureList.push_back(make_pair(procName, startEndLine));
	return procedureListIndex++;
}

void PKB::addFollows(int stmtBefore, int stmtAfter)
{
	while (followsList.size() <= (unsigned int) stmtBefore)
		followsList.push_back(0);
	followsList[stmtBefore] = stmtAfter;

	while (followsStarTable.size() <= (unsigned int) stmtAfter)
		followsStarTable.push_back(vector<bool>(stmtAfter));
	for (unsigned int i = 0; i < followsStarTable.size(); ++i) {
		while (followsStarTable[i].size() <= (unsigned int) stmtAfter)
			followsStarTable[i].push_back(false);
	}

	followsStarTable[stmtBefore][stmtAfter] = true;
	followsStarTable[stmtBefore][stmtBefore] = false;
	followsStarTable[stmtAfter][stmtAfter] = false;
	
	unsigned int i;
	for (i = 1; i <= (unsigned int) stmtBefore; ++i) {
		followsStarTable[i][stmtAfter] = followsStarTable[i][stmtBefore];
	}
	for (i = stmtAfter + 1; i <= followsStarTable[stmtBefore].size(); ++i) {
		followsStarTable[stmtBefore][i] = followsStarTable[stmtBefore][i];
	}
}

void PKB::addParent(int stmtParent, int stmtChild)
{
	while (parentList.size() <= (unsigned int) stmtChild)
		parentList.push_back(0);
	parentList[stmtChild] = stmtParent;

	while (parentStarTable.size() <= (unsigned int) stmtChild)
		parentStarTable.push_back(vector<bool>(stmtChild));
	for (unsigned int i = 0; i < parentStarTable.size(); ++i) {
		while (parentStarTable[i].size() <= (unsigned int) stmtChild)
			parentStarTable[i].push_back(false);
	}

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
	while (usesTable.size() <= (unsigned int)stmtNo)
		usesTable.push_back(vector<string>());
	usesTable[stmtNo].push_back(varName);
}

void PKB::addModifies(int stmtNo, string varName)
{
	while (modifiesTable.size() <= (unsigned int)stmtNo)
		modifiesTable.push_back(vector<string>());
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

vector< pair<int, string> > PKB::getAllAssignmentUsesVariablePairs()
{
	vector< pair<int, string> > result;
	for_each(assignList.begin(), assignList.end(),
		[&](int stmtNo) { for_each(usesTable[stmtNo].begin(), usesTable[stmtNo].end(),
			[&](string varName) { result.push_back(pair<int, string>(stmtNo, varName)); }); });
	return result;
}
vector< pair<int, string> > PKB::getAllStmtUsesVariablePairs()
{
	vector<int> stmts(usesTable.size());
	int n = 0;
	generate(stmts.begin(), stmts.end(), [&] {return ++n; });
	vector< pair<int, string> > result;
	for_each(stmts.begin(), stmts.end(),
		[&](int stmtNo) { for_each(usesTable[stmtNo].begin(), usesTable[stmtNo].end(),
			[&](string varName) { result.push_back(pair<int, string>(stmtNo, varName)); }); });
	return result;
}
vector< pair<string, string> > PKB::getAllProcedureUsesVariablePairs()
{
	vector< pair<string, string> > result;
	for_each(procedureList.begin(), procedureList.end(),
		[&](pair<string, pair<int, int> > procedure) {
		string procName = procedure.first;
		pair<int, int> stmtNoRange = procedure.second;
		vector<int> stmts(stmtNoRange.second - stmtNoRange.first + 1);
		int n = stmtNoRange.first;
		generate(stmts.begin(), stmts.end(), [&] {return n++; });
		for_each(stmts.begin(), stmts.end(), [&](int stmtNo) {
			for_each(usesTable[stmtNo].begin(), usesTable[stmtNo].end(), [&](string varName) {
				pair<string, string> procVarPair = make_pair(procedureList[0].first, varName);
				if (find(result.begin(), result.end(), procVarPair) == result.end())
					result.push_back(procVarPair); }); }); });
	return result;
}
vector<string> PKB::getAllVariablesUsedByStmtNo(int stmtNo)
{
	if ((unsigned int) stmtNo >= usesTable.size())
		return vector<string>();
	return usesTable[stmtNo];
}
vector<string> PKB::getAllVariablesUsedByProcedures(string procName)
{
	return vector<string>();
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

vector<pair<int, int>> PKB::getAllFollowsPair(bool star)
{
	return vector<pair<int, int>>();
}

vector<int> PKB::getStmtNoThatFollows(int stmtNo, bool star)
{
	return vector<int>();
}

vector<int> PKB::getStmtNoThatIsFollowedBy(int stmtNo, bool star)
{
	return vector<int>();
}

vector<pair<int, int>> PKB::getAllParentPair(bool star)
{
	return vector<pair<int, int>>();
}

vector<int> PKB::getStmtNoThatIsChildOf(int stmtNo, bool star)
{
	return vector<int>();
}

vector<int> PKB::getStmtNoThatIsParentOf(int stmtNo, bool star)
{
	return vector<int>();
}

vector<int> PKB::getAllStmtThatUses(string v)
{
	vector<int> stmts(usesTable.size());
	vector<int> result;
	int n = 0;
	generate(stmts.begin(), stmts.end(), [&] {return ++n;});
	copy_if(stmts.begin(), stmts.end(), back_inserter(result),
		[=](int stmtNo) { return PKB::isUses(stmtNo, v); });
	return result;
}

vector<int> PKB::getAllAssignmentThatUses(string v)
{
	vector<int> result;
	copy_if(assignList.begin(), assignList.end(), back_inserter(result),
		[=](int assignStmtNo) { return PKB::isUses(assignStmtNo, v); });
	return result;
}

vector<int> PKB::getAllPrintThatUses(string varName)
{
	return vector<int>();
}

vector<int> PKB::getAllIfThatUses(string varName)
{
	return vector<int>();
}

vector<int> PKB::getAllWhileThatUses(string varName)
{
	return vector<int>();
}

vector<string> PKB::getAllProcedureThatUses(string varName)
{
	return vector<string>();
}

vector<int> PKB::getAllStmtThatModifies(string v)
{
	vector<int> stmts(modifiesTable.size());
	vector<int> result;
	int n = 0;
	generate(stmts.begin(), stmts.end(), [&] {return ++n; });
	copy_if(stmts.begin(), stmts.end(), back_inserter(result),
		[=](int stmtNo) { return PKB::isModifies(stmtNo, v); });
	return result;
}

vector<int> PKB::getAllAssignmentThatModifies(string v)
{
	vector<int> result;
	copy_if(assignList.begin(), assignList.end(), back_inserter(result),
		[=](int assignStmtNo) { return PKB::isModifies(assignStmtNo, v); });
	return result;
}

vector<int> PKB::getAllReadThatModifies(string varName)
{
	return vector<int>();
}

vector<int> PKB::getAllIfThatModifies(string varName)
{
	return vector<int>();
}

vector<int> PKB::getAllWhileThatModifies(string varName)
{
	return vector<int>();
}

vector<string> PKB::getAllProcedureThatModifies(string varName)
{
	return vector<string>();
}

vector< pair<int, string> > PKB::getAllAssignmentModifiesVariablePairs()
{
	vector< pair<int, string> > result;
	for_each(assignList.begin(), assignList.end(),
		[&](int stmtNo) { for_each(modifiesTable[stmtNo].begin(), modifiesTable[stmtNo].end(),
			[&](string varName) { result.push_back(pair<int, string>(stmtNo, varName)); }); });
	return result;
}

vector< pair<int, string> > PKB::getAllStmtModifiesVariablePairs()
{
	vector<int> stmts(modifiesTable.size());
	int n = 0;
	generate(stmts.begin(), stmts.end(), [&] {return ++n; });
	vector< pair<int, string> > result;
	for_each(stmts.begin(), stmts.end(),
		[&](int stmtNo) { for_each(modifiesTable[stmtNo].begin(), modifiesTable[stmtNo].end(),
			[&](string varName) { result.push_back(pair<int, string>(stmtNo, varName)); }); });
	return result;
}

vector< pair<string, string> > PKB::getAllProcedureModifiesVariablePairs()
{
	vector< pair<string, string> > result;
	for_each(procedureList.begin(), procedureList.end(),
		[&](pair<string, pair<int, int> > procedure) {
		string procName = procedure.first;
		pair<int, int> stmtNoRange = procedure.second;
		vector<int> stmts(stmtNoRange.second - stmtNoRange.first + 1);
		int n = stmtNoRange.first;
		generate(stmts.begin(), stmts.end(), [&] {return n++; });
		for_each(stmts.begin(), stmts.end(), [&](int stmtNo) {
			for_each(usesTable[stmtNo].begin(), usesTable[stmtNo].end(), [&](string varName) { 
				pair<string, string> procVarPair = make_pair(procName, varName);
				if (find(result.begin(), result.end(), procVarPair) == result.end())
					result.push_back(procVarPair);
	}); }); });
	return result;
}

vector<string> PKB::getAllVariablesModifiedByStmtNo(int stmtNo)
{
	if ((unsigned int)stmtNo >= modifiesTable.size())
		return vector<string>();
	return modifiesTable[stmtNo];
}

vector<string> PKB::getAllVariablesModifiedByProcedures(string procName)
{
	return vector<string>();
}

vector<string> PKB::getVariables()
{
	return varList;
}

vector<int> PKB::getAssigns()
{
	return assignList;
}

vector<int> PKB::getReads()
{
	return readList;
}

vector<int> PKB::getPrints()
{
	return printList;
}

vector<int> PKB::getIfs()
{
	return ifList;
}

vector<int> PKB::getWhiles()
{
	return whileList;
}

vector< pair<string, pair<int, int> > > PKB::getProcedures()
{
	return procedureList;
}
