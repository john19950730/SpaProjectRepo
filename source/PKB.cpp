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

/****************************************
|										|
|		PKB Synonyms Storage			|
|										|
****************************************/

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
static vector<string> procedureList;
static unsigned int procedureListIndex = 0;
static vector<unsigned int> synonymsList[] = { stmtsList, assignList, ifList, whileList, readList, printList, callList };

/****************************************
|										|
|		PKB Relations Storage			|
|										|
****************************************/

// element at index i means Follows(i, element) holds
static vector<unsigned int> followsList;
// element at index i, j means Follows*(i, j) holds
static vector< vector<bool> > followsStarTable;

// element at index i means Parent(element, i) holds
static vector<unsigned int> parentList;
// element at index i, j means Parent*(i, j) holds
static vector< vector<bool> > parentStarTable;

// array at index i of usesTable[i] contains list of variables v where Uses(i, v) holds
static vector< vector<string> > usesTable;
// maps procedure name to list of variables used in the procedure
static unordered_map<string, vector<string> > procedureUsesTable;

// array at index i of modifiesTable[i] contains list of variables v where Modifies(i, v) holds
static vector< vector<string> > modifiesTable;
// maps procedure name to list of variables modified in the procedure
static unordered_map<string, vector<string> > procedureModifiesTable;

/****************************************
|										|
|			PKB Population				|
|										|
****************************************/

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

unsigned int PKB::addProcedure(string procName)
{
	procedureList.push_back(procName);
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

void PKB::addProcedureUses(string procName, string varName)
{
	//verify that procName is a registered procedure in PKB
	//TODO for modifies, abstract
	if (!procedureExists(procName))
		return;
	if (!hasProcedureUses(procName))
		procedureUsesTable.insert(make_pair(procName, vector<string>()));
	if (find(procedureUsesTable[procName].begin(), procedureUsesTable[procName].end(), varName) == procedureUsesTable[procName].end())
		procedureUsesTable[procName].push_back(varName);
}

void PKB::addModifies(unsigned int stmtNo, string varName)
{
	while (modifiesTable.size() <= stmtNo)
		modifiesTable.push_back(vector<string>());
	if (find(modifiesTable[stmtNo].begin(), modifiesTable[stmtNo].end(), varName) == modifiesTable[stmtNo].end())
	modifiesTable[stmtNo].push_back(varName);
}

void PKB::addProcedureModifies(string procName, string varName)
{
	if (!procedureExists(procName))
		return;
	if (!hasProcedureModifies(procName))
		procedureModifiesTable.insert(make_pair(procName, vector<string>()));
	if (find(procedureModifiesTable[procName].begin(), procedureModifiesTable[procName].end(), varName) == procedureModifiesTable[procName].end())
		procedureModifiesTable[procName].push_back(varName);
}

/****************************************
|										|
|	PKB Follows Relations Queries		|
|										|
****************************************/

//represents Follows(1, 2) or Follows*(1, 2)
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

//represents Follows(1, _) or Follows*(1, _)
bool PKB::hasFollows(unsigned int stmtNo1, bool star)
{
	//TODO
	return false;
}

//represents Follows(_, 2) or Follows*(_, 2)
bool PKB::hasFollowedBy(unsigned int stmtNo2, bool star)
{
	//TODO
	return false;
}

//represents Follows(_, _) or Follows*(_, _)
bool PKB::hasFollowsPair(bool star)
{
	//TODO
	return false;
}

//represents Follows(a, b) or Follows*(a, b)
vector<pair<unsigned int, unsigned int>> PKB::getAllFollowsPair(string synonym1, string synonym2, bool star)
{
	//TODO
	return vector<pair<unsigned int, unsigned int>>();
}

//represents Follows(a, _) or Follows*(a, _)
vector<unsigned int> PKB::getAllFollowedStmts(string synonym1, bool star)
{
	//TODO
	return vector<unsigned int>();
}

//represents Follows(a, 2) or Follows*(a, 2)
vector<unsigned int> PKB::getAllStmtsFollowedBy(string synonym1, unsigned int stmtNo2, bool star)
{
	//TODO
	return vector<unsigned int>();
}

//represents: Follows(_, b) or Follows*(_, b)
vector<unsigned int> PKB::getAllFollowsStmts(string synonym2, bool star)
{
	//TODO
	return vector<unsigned int>();
}

//represents: Follows(1, b) or Follows*(1, b)
vector<unsigned int> PKB::getAllStmtsThatFollows(unsigned int stmtNo1, string synonym2, bool star)
{
	//TODO
	return vector<unsigned int>();
}

/****************************************
|										|
|		PKB Parent Relations Query		|
|										|
****************************************/

//represents: Parent(1, 2) or Parent*(1, 2)
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

//represents: Parent(1, _), Parent*(1, _)
bool PKB::hasChild(unsigned int stmtNo1, bool star)
{
	//TODO
	return false;
}

//represents: Parent(_, 2) or Parent*(_, 2)
bool PKB::hasParent(unsigned int stmtNo2, bool star)
{
	//TODO
	return false;
}

//represents: Parent(_, _) or Parent*(_, _)
bool PKB::hasParentPair(bool star)
{
	//TODO
	return false;
}

//represents: Parent(a, b) or Parent*(a, b)
vector<pair<unsigned int, unsigned int>> PKB::getAllParentPair(string synonym1, string synonym2, bool star)
{
	//TODO
	return vector<pair<unsigned int, unsigned int>>();
}

//represents: Parent(a, _) or Parent*(a, _)
vector<unsigned int> PKB::getAllParentStmts(string synonym1, bool star)
{
	//TODO
	return vector<unsigned int>();
}

//represents: Parent(a, 2) or Parent*(a, 2)
vector<unsigned int> PKB::getAllStmtsThatIsParentOf(string synonym1, unsigned int stmtNo2, bool star)
{
	//TODO
	return vector<unsigned int>();
}

//represents: Parent(_, b) or Parent*(_, b)
vector<unsigned int> PKB::getAllChildStmts(string synonym2, bool star)
{
	//TODO
	return vector<unsigned int>();
}

//represents: Parent(1, b) or Parent*(1, b)
vector<unsigned int> PKB::getAllStmtsThatIsChildOf(unsigned int stmtNo1, string synonym2, bool star)
{
	//TODO
	return vector<unsigned int>();
}

/****************************************
|										|
|		PKB Uses Relations Query		|
|										|
****************************************/

//represents: Uses(1, "var")
bool PKB::isUses(unsigned int stmtNo, string varName)
{
	if (stmtNo >= usesTable.size())
		return false;
	return find(usesTable[stmtNo].begin(), usesTable[stmtNo].end(), varName) != usesTable[stmtNo].end();
}

//represents: Uses(1, _)
bool PKB::hasUses(unsigned int stmtNo1)
{
	//TODO
	return false;
}

//represents Uses(1, v)
vector<string> PKB::getAllVariablesUsedByStmtNo(unsigned int stmtNo)
{
	if ((unsigned int)stmtNo >= usesTable.size())
		return vector<string>();
	return usesTable[stmtNo];
}

//represents: Uses(a, "var")
vector<unsigned int> PKB::getAllStmtsThatUsesVariable(string synonym, string varName)
{
	vector<unsigned int> stmts = getAllStmtsThatFitSynonym(synonym);
	vector<unsigned int> result;
	copy_if(stmts.begin(), stmts.end(), back_inserter(result),
		[=](unsigned int stmtNo) { return PKB::isUses(stmtNo, varName); });
	return result;
}

//represents: Uses(a, _)
vector<unsigned int> PKB::getAllStmtsThatUses(string synonym)
{
	//TODO
	return vector<unsigned int>();
}

//represents Uses(a, v)
vector< pair<unsigned int, string> > PKB::getAllStmtUsesVariablePairs(string synonym)
{
	vector<unsigned int> stmts = getAllStmtsThatFitSynonym(synonym);
	vector< pair<unsigned int, string> > result;
	for_each(stmts.begin(), stmts.end(),
		[&](int stmtNo) { for_each(usesTable[stmtNo].begin(), usesTable[stmtNo].end(),
			[&](string varName) { result.push_back(pair<unsigned int, string>(stmtNo, varName)); }); });
	return result;
}

//represents Uses("proc", "var")
bool PKB::isProcedureUses(string procName, string varName)
{
	//TODO
	return false;
}

//represents Uses("proc", _)
bool PKB::hasProcedureUses(string procName)
{
	//TODO
	return false;
}

//represents Uses("proc", v)
vector<string> PKB::getAllVariablesUsedByProcedure(string procName)
{
	//TODO
	return vector<string>();
}

//represents: Uses(p, "var")
vector<string> PKB::getAllProceduresThatUsesVariable(string varName)
{
	//TODO
	return vector<string>();
}

//represents: Uses(p, _)
vector<string> PKB::getAllProceduresThatUses()
{
	//TODO
	return vector<string>();
}

//represents Uses(p, v)
vector< pair<string, string> > PKB::getAllProcedureUsesVariablePairs()
{
	vector< pair<string, string> > result;
	//TODO
	return result;
}

/****************************************
|										|
|	PKB Modifies Relations Query		|
|										|
****************************************/

//represents: Modifies(1, "var")
bool PKB::isModifies(unsigned int stmtNo, string varName)
{
	if (stmtNo >= modifiesTable.size())
		return false;
	return find(modifiesTable[stmtNo].begin(), modifiesTable[stmtNo].end(), varName) != modifiesTable[stmtNo].end();
}

//represents: Modifies(1, _)
bool PKB::hasModifies(unsigned int stmtNo1)
{
	//TODO
	return false;
}

//represents: Modifies(1, v)
vector<string> PKB::getAllVariablesModifiedByStmtNo(unsigned int stmtNo)
{
	if ((unsigned int)stmtNo >= modifiesTable.size())
		return vector<string>();
	return modifiesTable[stmtNo];
}

//represents: Modifies(a, "var")
vector<unsigned int> PKB::getAllStmtThatModifiesVariable(string synonym, string varName)
{
	vector<unsigned int> stmts = getAllStmtsThatFitSynonym(synonym);
	vector<unsigned int> result;
	int n = 0;
	generate(stmts.begin(), stmts.end(), [&] {return ++n; });
	copy_if(stmts.begin(), stmts.end(), back_inserter(result),
		[=](unsigned int stmtNo) { return PKB::isModifies(stmtNo, varName); });
	return result;
}

//represents: Modifies(a, _)
vector<unsigned int> PKB::getAllStmtThatModifies(string synonym)
{
	//TODO
	return vector<unsigned int>();
}

//represents: Modifies(a, v)
vector< pair<unsigned int, string> > PKB::getAllStmtModifiesVariablePairs(string synonym)
{
	vector<unsigned int> stmts = getAllStmtsThatFitSynonym(synonym);
	vector< pair<unsigned int, string> > result;
	for_each(stmts.begin(), stmts.end(),
		[&](unsigned int stmtNo) { for_each(modifiesTable[stmtNo].begin(), modifiesTable[stmtNo].end(),
			[&](string varName) { result.push_back(pair<unsigned int, string>(stmtNo, varName)); }); });
	return result;
}

//represents: Modifies("proc", "var")
bool PKB::isProcedureModifies(string procName, string varName)
{
	//TODO
	return false;
}

//represents: Modifies("proc", _)
bool PKB::hasProcedureModifies(string procName)
{
	bool result = false;
	for_each(procedureModifiesTable.begin(), procedureModifiesTable.end(), [&](pair<string, vector<string> > procM) {
		if (exactMatch(procM.first, procName) && procM.second.size() > 0)
			result = true;
	});
	return result;
}

//represents: Modifies("proc", v)
vector<string> PKB::getAllVariablesModifiedByProcedure(string procName)
{
	if (!hasProcedureModifies(procName))
		return vector<string>();
	return procedureModifiesTable[procName];
}

//represents: Modifies(p, "var")
vector<string> PKB::getAllProceduresThatModifiesVariable(string varName)
{
	//TODO
	return vector<string>();
}

//represents: Modifies(p, _)
vector<string> PKB::getAllProceduresThatModifies()
{
	//TODO
	return vector<string>();
}

//represents: Modifies(p, v)
vector< pair<string, string> > PKB::getAllProcedureModifiesVariablePairs()
{
	vector< pair<string, string> > result;
	for_each(procedureModifiesTable.begin(), procedureModifiesTable.end(), [&](pair<string, vector<string> > procModifiesPair) {
		for_each(procModifiesPair.second.begin(), procModifiesPair.second.end(), [&](string modifies) {
			result.push_back(make_pair(procModifiesPair.first, modifies));
		});
	});
	return result;
}

vector<unsigned int> PKB::getAllAssignsWithConstant(string constant)
{
	return vector<unsigned int>();
}

bool PKB::hasAssignmentStmt()
{
	return false;
}

bool PKB::isAssignmentUsesConstant(unsigned int stmtNo, string constant)
{
	return false;
}

/****************************************
|										|
|			PKB Synonyms Query			|
|										|
****************************************/

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

vector<string> PKB::getProcedureNames()
{
	return procedureList;
}

vector<unsigned int> PKB::getAllStmtsThatFitSynonym(string synonym)
{
	for (unsigned int i = 0; i < STATEMENTS->size(); ++i) {
		if (exactMatch(synonym, STATEMENTS[i]))
			return synonymsList[i];
	}
	return vector<unsigned int>();
}

/****************************************
|										|
|		PKB Private Utilities			|
|										|
****************************************/

unsigned int PKB::addStatement(unsigned int stmtNo)
{
	stmtsList.push_back(stmtNo);
	return totalLines++;
}

bool PKB::procedureExists(string procName)
{
	return find(procedureList.begin(), procedureList.end(), procName) != procedureList.end();
}

bool PKB::exactMatch(string s1, string s2)
{
	return s1.find(s2) == 0 && s1.length() == s2.length();
}
