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

static const string STMT_VAR = "stmt";
static const string ASSIGNMENT_VAR = "assign";
static const string IF_VAR = "if";
static const string WHILE_VAR = "while";
static const string READ_VAR = "read";
static const string PRINT_VAR = "print";
static const string CALL_VAR = "call";
static const string STATEMENTS[] = { STMT_VAR, ASSIGNMENT_VAR, IF_VAR, WHILE_VAR, READ_VAR, PRINT_VAR, CALL_VAR };

static vector<unsigned int> stmtsList;
static unsigned int totalLines = 0;
static vector<string> varList;
static unsigned int varListIndex = 0;
static vector<unsigned int> assignList;
static unsigned int assignListIndex = 0;
static vector<unsigned int> ifList;
static unsigned int ifListIndex = 0;
static vector<unsigned int> whileList;
static unsigned int whileListIndex = 0;
static vector<unsigned int> readList;
static unsigned int readListIndex = 0;
static vector<unsigned int> printList;
static unsigned int printListIndex = 0;
static vector<unsigned int> callList;
static unsigned int callListIndex;
static unordered_map<string, pair<unsigned int, unsigned int> > procedureMap;
static unsigned int procedureListIndex = 0;
static vector<unsigned int> synonymsList[] = { stmtsList, assignList, ifList, whileList, readList, printList, callList };

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

unsigned int PKB::addVariable(string varName)
{
	if (find(varList.begin(), varList.end(), varName) != varList.end())
		return varListIndex;
	varList.push_back(varName);
	return varListIndex++;
}

unsigned int PKB::addAssign(unsigned int stmtNo)
{
	assignList.push_back(stmtNo);
	PKB::addStatement(stmtNo);
	return assignListIndex++;
}

unsigned int PKB::addIf(unsigned int stmtNo)
{
	ifList.push_back(stmtNo);
	PKB::addStatement(stmtNo);
	return ifListIndex++;
}

unsigned int PKB::addWhile(unsigned int stmtNo)
{
	whileList.push_back(stmtNo);
	PKB::addStatement(stmtNo);
	return whileListIndex++;
}

unsigned int PKB::addRead(unsigned int stmtNo)
{
	readList.push_back(stmtNo);
	PKB::addStatement(stmtNo);
	return readListIndex++;
}

unsigned int PKB::addPrint(unsigned int stmtNo)
{
	printList.push_back(stmtNo);
	PKB::addStatement(stmtNo);
	return printListIndex++;
}

unsigned int PKB::addCall(unsigned int stmtNo)
{
	callList.push_back(stmtNo);
	PKB::addStatement(stmtNo);
	return callListIndex++;
}

unsigned int PKB::addProcedure(string procName, pair<unsigned int, unsigned int> startEndLine)
{
	procedureMap.insert(make_pair(procName, startEndLine));
	return procedureListIndex++;
}

void PKB::addFollows(unsigned int stmtBefore, unsigned int stmtAfter)
{
	while (followsList.size() <= stmtBefore)
		followsList.push_back(0);
	followsList[stmtBefore] = stmtAfter;

	while (followsStarTable.size() <= stmtAfter)
		followsStarTable.push_back(vector<bool>(stmtAfter));
	for (unsigned int i = 0; i < followsStarTable.size(); ++i) {
		while (followsStarTable[i].size() <= stmtAfter)
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

void PKB::addParent(unsigned int stmtParent, unsigned int stmtChild)
{
	while (parentList.size() <= stmtChild)
		parentList.push_back(0);
	parentList[stmtChild] = stmtParent;

	while (parentStarTable.size() <= stmtChild)
		parentStarTable.push_back(vector<bool>(stmtChild));
	for (unsigned int i = 0; i < parentStarTable.size(); ++i) {
		while (parentStarTable[i].size() <= stmtChild)
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

void PKB::addUses(unsigned int stmtNo, string varName)
{
	while (usesTable.size() <= stmtNo)
		usesTable.push_back(vector<string>());
	if (find(usesTable[stmtNo].begin(), usesTable[stmtNo].end(), varName) == usesTable[stmtNo].end())
		usesTable[stmtNo].push_back(varName);
}

void PKB::addModifies(unsigned int stmtNo, string varName)
{
	while (modifiesTable.size() <= stmtNo)
		modifiesTable.push_back(vector<string>());
	if (find(modifiesTable[stmtNo].begin(), modifiesTable[stmtNo].end(), varName) == modifiesTable[stmtNo].end())
	modifiesTable[stmtNo].push_back(varName);
}

bool PKB::isFollows(unsigned int stmtNo1, unsigned int stmtNo2, bool star)
{
	if (stmtNo1 >= followsList.size() || stmtNo2 >= followsList.size())
		return false;
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
	for_each(procedureMap.begin(), procedureMap.end(),
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
					result.push_back(procVarPair); }); }); });
	return result;
}
vector<string> PKB::getAllVariablesUsedByStmtNo(unsigned int stmtNo)
{
	if ((unsigned int) stmtNo >= usesTable.size())
		return vector<string>();
	return usesTable[stmtNo];
}
vector<string> PKB::getAllVariablesUsedByProcedures(string procName)
{
	unordered_map<string, pair<unsigned int, unsigned int> >::const_iterator procedure = procedureMap.find(procName);
	if (procedure == procedureMap.end())
		return vector<string>();
	vector<string> result;
	pair<int, int> stmtNoRange = procedure->second;
	vector<int> stmts(stmtNoRange.second - stmtNoRange.first + 1);
	int n = stmtNoRange.first;
	generate(stmts.begin(), stmts.end(), [&] {return n++; });
	for_each(stmts.begin(), stmts.end(), [&](int stmtNo) {
		for_each(usesTable[stmtNo].begin(), usesTable[stmtNo].end(), [&](string varName) {
			if (find(result.begin(), result.end(), varName) == result.end())
				result.push_back(varName);
		}); });
	return result;
}
bool PKB::isParent(unsigned int stmtNo1, unsigned int stmtNo2, bool star)
{
	if (stmtNo1 >= parentList.size() || stmtNo2 >= parentList.size())
		return false;
	if (!star) {
		return parentList[stmtNo2] == stmtNo1;
	}
	else {
		return parentStarTable[stmtNo1][stmtNo2];
	}
}

bool PKB::isUses(unsigned int stmtNo, string varName)
{
	if (stmtNo >= usesTable.size())
		return false;
	return find(usesTable[stmtNo].begin(), usesTable[stmtNo].end(), varName) != usesTable[stmtNo].end();
}

bool PKB::isModifies(unsigned int stmtNo, string varName)
{
	if (stmtNo >= modifiesTable.size())
		return false;
	return find(modifiesTable[stmtNo].begin(), modifiesTable[stmtNo].end(), varName) != modifiesTable[stmtNo].end();
}

vector<pair<int, int>> PKB::getAllFollowsPair(bool star)
{
	//TODO
	return vector<pair<int, int>>();
}

vector<int> PKB::getStmtNoThatFollows(int stmtNo, bool star)
{
	//TODO
	return vector<int>();
}

vector<int> PKB::getStmtNoThatIsFollowedBy(int stmtNo, bool star)
{
	//TODO
	return vector<int>();
}

vector<pair<int, int>> PKB::getAllParentPair(bool star)
{
	//TODO
	return vector<pair<int, int>>();
}

vector<int> PKB::getStmtNoThatIsChildOf(int stmtNo, bool star)
{
	//TODO
	return vector<int>();
}

vector<int> PKB::getStmtNoThatIsParentOf(int stmtNo, bool star)
{
	//TODO
	return vector<int>();
}

vector<unsigned int> PKB::getAllStmtThatUses(string synonym, string v)
{
	vector<unsigned int> stmts = getAllStmtsThatFitSynonym(synonym);
	vector<unsigned int> result;
	copy_if(stmts.begin(), stmts.end(), back_inserter(result),
		[=](unsigned int stmtNo) { return PKB::isUses(stmtNo, v); });
	return result;
}

vector<string> PKB::getAllProcedureThatUses(string varName)
{
	//TODO
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
	//TODO
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
	for_each(procedureMap.begin(), procedureMap.end(),
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

vector<string> PKB::getAllVariablesModifiedByStmtNo(unsigned int stmtNo)
{
	if ((unsigned int)stmtNo >= modifiesTable.size())
		return vector<string>();
	return modifiesTable[stmtNo];
}

vector<string> PKB::getAllVariablesModifiedByProcedures(string procName)
{
	unordered_map<string, pair<unsigned int, unsigned int> >::const_iterator procedure = procedureMap.find(procName);
	if (procedure == procedureMap.end())
		return vector<string>();
	vector<string> result;
	pair<int, int> stmtNoRange = procedure->second;
	vector<int> stmts(stmtNoRange.second - stmtNoRange.first + 1);
	int n = stmtNoRange.first;
	generate(stmts.begin(), stmts.end(), [&] {return n++; });
	for_each(stmts.begin(), stmts.end(), [&](int stmtNo) {
		for_each(modifiesTable[stmtNo].begin(), modifiesTable[stmtNo].end(), [&](string varName) {
			if (find(result.begin(), result.end(), varName) == result.end())
				result.push_back(varName);
	}); });
	return result;
}

vector<string> PKB::getVariables()
{
	return varList;
}

vector<unsigned int> PKB::getAllStmts()
{
	return stmtsList;
}

vector<unsigned int> PKB::getAssigns()
{
	return assignList;
}

vector<unsigned int> PKB::getIfs()
{
	return ifList;
}

vector<unsigned int> PKB::getWhiles()
{
	return whileList;
}

vector<unsigned int> PKB::getReads()
{
	return readList;
}

vector<unsigned int> PKB::getPrints()
{
	return printList;
}

vector<unsigned int> PKB::getCalls()
{
	return callList;
}

unordered_map<string, pair<unsigned int, unsigned int> > PKB::getProcedures()
{
	return procedureMap;
}

vector<string> PKB::getProcedureNames()
{
	vector<string> result;
	for_each(procedureMap.begin(), procedureMap.end(), [&] (pair<string, pair<int, int> > procedurePair) {
		result.push_back(procedurePair.first);
	});
	return result;
}

vector<unsigned int> PKB::getAllStmtsThatFitSynonym(string synonym)
{
	string::const_iterator it = find(STATEMENTS->begin(), STATEMENTS->end(), synonym);
	if (it == STATEMENTS->end())
		return vector<unsigned int>();
	return synonymsList[it - STATEMENTS->begin()];
}

unsigned int PKB::addStatement(unsigned int stmtNo)
{
	stmtsList.push_back(stmtNo);
	return totalLines++;
}
