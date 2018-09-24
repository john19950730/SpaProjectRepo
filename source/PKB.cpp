#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "Keywords.h"

using namespace keywords::query;

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
static unsigned int callListIndex = 0;
static vector<string> procedureList;
static unsigned int procedureListIndex = 0;
static vector<unsigned int> * synonymsList[] = { &stmtsList, &assignList, &ifList, &whileList, &readList, &printList, &callList };

/****************************************
|										|
|		PKB Relations Storage			|
|										|
****************************************/

// element at key i means Follows(i, element) holds
static map<unsigned int, unsigned int> followsList;
// element at key i means Follows(element, i) holds
static map<unsigned int, unsigned int> followedList;
// element at index i, j means Follows*(i, j) holds
static map<pair<unsigned int, unsigned int>, bool > followsStarTable;
// Follows*(i, j) holds for each element j in list at index i, filtered by synonym type
static map<string, map<unsigned int, vector<unsigned int> > > followsStarList;
// Follows*(i, j) holds for each element i in list at index j, filtered by synonym type
static map<string, map<unsigned int, vector<unsigned int> > > followedStarList;
// Follows pair storage, maps synonym pairs to appropriate follows pair
static map<pair<string, string>, vector<pair<unsigned int, unsigned int> > > followsPairs;
static map<pair<string, string>, vector<pair<unsigned int, unsigned int> > > followsStarPairs;

// element at key i means Parent(element, i) holds
static map<unsigned int, unsigned int> parentList;
// elements at key i means Parent(i, element) holds
static map<unsigned int, vector<unsigned int> > childList;
// element at index i, j means Parent*(i, j) holds
static map<pair<unsigned int, unsigned int>, bool> parentStarTable;
// Parent*(i, j) holds for each element i in list at index j, filtered by synonym type
static map<string, map<unsigned int, vector<unsigned int> > > parentStarList;
// Parent*(i, j) holds for each element j in list at index i, filtered by synonym type
static map<string, map<unsigned int, vector<unsigned int> > > childStarList;
// Parent pair storage, maps synonym pairs to appropriate parent pair
static map<pair<string, string>, vector<pair<unsigned int, unsigned int> > > parentPairs;
static map<pair<string, string>, vector<pair<unsigned int, unsigned int> > > parentStarPairs;

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
|			PKB De-population			|
|										|
****************************************/
void PKB::clearPKB()
{
	stmtsList = vector<unsigned int>();
	totalLines = 0;
	varList = vector<string>();
	varListIndex = 0;
	assignList = vector<unsigned int>();
	assignListIndex = 0;
	ifList = vector<unsigned int>();
	ifListIndex = 0;
	whileList = vector<unsigned int>();
	whileListIndex = 0;
	readList = vector<unsigned int>();
	readListIndex = 0;
	printList = vector<unsigned int>();
	printListIndex = 0;
	callList = vector<unsigned int>();
	callListIndex = 0;
	procedureList = vector<string>();
	procedureListIndex = 0;

	followsList = map<unsigned int, unsigned int>();
	followedList = map<unsigned int, unsigned int>();
	followsStarTable = map<pair<unsigned int, unsigned int>, bool >();
	followsStarList = map<string, map<unsigned int, vector<unsigned int> > >();
	followedStarList = map<string, map<unsigned int, vector<unsigned int> > >();
	followsPairs = map<pair<string, string>, vector<pair<unsigned int, unsigned int> > >();
	followsStarPairs = map<pair<string, string>, vector<pair<unsigned int, unsigned int> > >();

	parentList = map<unsigned int, unsigned int>();
	childList = map<unsigned int, vector<unsigned int> >();
	parentStarTable = map<pair<unsigned int, unsigned int>, bool >();
	parentStarList = map<string, map<unsigned int, vector<unsigned int> > >();
	childStarList = map<string, map<unsigned int, vector<unsigned int> > >();
	parentPairs = map<pair<string, string>, vector<pair<unsigned int, unsigned int> > >();
	parentStarPairs = map<pair<string, string>, vector<pair<unsigned int, unsigned int> > >();

	//TODO: add more resets after Uses and Modifies tables are revamped

}

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
	procedureModifiesTable.insert(make_pair(procName, vector<string>()));
	procedureUsesTable.insert(make_pair(procName, vector<string>()));
	return procedureListIndex++;
}

void PKB::addFollows(unsigned int stmtBefore, unsigned int stmtAfter)
{
	followsList[stmtBefore] = stmtAfter;
	followedList[stmtAfter] = stmtBefore;

	followsStarTable[make_pair(stmtBefore, stmtAfter)] = true;
	followsStarList[STMT_VAR][stmtBefore].push_back(stmtAfter);
	followsStarList[getSynonymTypeOfStmt(stmtBefore)][stmtBefore].push_back(stmtAfter);
	followedStarList[STMT_VAR][stmtAfter].push_back(stmtBefore);
	followedStarList[getSynonymTypeOfStmt(stmtAfter)][stmtAfter].push_back(stmtBefore);

	addFollowsPair(stmtBefore, stmtAfter, false);
	addFollowsPair(stmtBefore, stmtAfter, true);

	unsigned int i;
	for (i = 1; i <= stmtBefore; ++i) {
		if (followsStarTable[make_pair(i, stmtBefore)]) {
			followsStarTable[make_pair(i, stmtAfter)] = followsStarTable[make_pair(i, stmtBefore)];
			followsStarList[STMT_VAR][i].push_back(stmtAfter);
			followsStarList[getSynonymTypeOfStmt(i)][i].push_back(stmtAfter);
			addFollowsPair(i, stmtAfter, true);
		}
	}
	for (i = stmtAfter + 1; i <= totalLines; ++i) {
		if (followsStarTable[make_pair(stmtAfter, i)]) {
			followsStarTable[make_pair(stmtBefore, i)] = followsStarTable[make_pair(stmtAfter, i)];
			followedStarList[STMT_VAR][i].push_back(stmtBefore);
			followedStarList[getSynonymTypeOfStmt(i)][i].push_back(stmtBefore);
			addFollowsPair(stmtBefore, i, true);
		}
	}
}

void PKB::addParent(unsigned int stmtParent, unsigned int stmtChild)
{
	parentList[stmtChild] = stmtParent;
	childList[stmtParent].push_back(stmtChild);

	parentStarTable[make_pair(stmtParent, stmtChild)] = true;
	parentStarList[STMT_VAR][stmtParent].push_back(stmtChild);
	parentStarList[getSynonymTypeOfStmt(stmtParent)][stmtParent].push_back(stmtChild);
	childStarList[STMT_VAR][stmtChild].push_back(stmtParent);
	childStarList[getSynonymTypeOfStmt(stmtChild)][stmtChild].push_back(stmtParent);

	addParentPair(stmtParent, stmtChild, false);
	addParentPair(stmtParent, stmtChild, true);

	unsigned int i;
	for (i = 1; i <= stmtParent; ++i) {
		if (parentStarTable[make_pair(i, stmtParent)]) {
			parentStarTable[make_pair(i, stmtChild)] = parentStarTable[make_pair(i, stmtParent)];
			parentStarList[STMT_VAR][i].push_back(stmtChild);
			parentStarList[getSynonymTypeOfStmt(i)][i].push_back(stmtChild);
			addParentPair(i, stmtChild, true);
		}
	}
	for (i = stmtChild + 1; i <= totalLines; ++i) {
		if (parentStarTable[make_pair(stmtChild, i)]) {
			parentStarTable[make_pair(stmtParent, i)] = parentStarTable[make_pair(stmtChild, i)];
			childStarList[STMT_VAR][i].push_back(stmtParent);
			childStarList[getSynonymTypeOfStmt(i)][i].push_back(stmtParent);
			addParentPair(stmtParent, i, true);
		}
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
	if (!procedureExists(procName))
		return;
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
	return (!star && followsList[stmtNo1] == stmtNo2) ||
		(star && followsStarTable[make_pair(stmtNo1, stmtNo2)]);
}

//represents Follows(1, _) or Follows*(1, _)
bool PKB::hasFollows(unsigned int stmtNo1, bool star)
{
	return (!star && followsList[stmtNo1] != 0) ||
		(star && followsStarList[STMT_VAR][stmtNo1].size() != 0);
}

//represents Follows(_, 2) or Follows*(_, 2)
bool PKB::hasFollowedBy(unsigned int stmtNo2, bool star)
{
	return (!star && followedList[stmtNo2] != 0) ||
		(star && followedStarList[STMT_VAR][stmtNo2].size() != 0);
}

//represents Follows(_, _) or Follows*(_, _)
bool PKB::hasFollowsPair(bool star)
{
	return followsList[1] != 0;
}

//represents Follows(a, b) or Follows*(a, b)
vector<pair<unsigned int, unsigned int> > PKB::getAllFollowsPair(string synonym1, string synonym2, bool star)
{
	if (!star)
		return followsPairs[make_pair(synonym1, synonym2)];
	return followsStarPairs[make_pair(synonym1, synonym2)];
}

//represents Follows(a, _) or Follows*(a, _)
vector<unsigned int> PKB::getAllFollowedStmts(string synonym1, bool star)
{
	vector<unsigned int> stmts = getAllStmtsThatFitSynonym(synonym1);
	vector<unsigned int> result;
	copy_if(stmts.begin(), stmts.end(), back_inserter(result), [=](unsigned int stmtNo) {
		return hasFollows(stmtNo, star);
	});
	return result;
}

//represents Follows(a, 2) or Follows*(a, 2)
vector<unsigned int> PKB::getAllStmtsFollowedBy(string synonym1, unsigned int stmtNo2, bool star)
{
	vector<unsigned int> result;
	if (!star && exactMatch(synonym1, getSynonymTypeOfStmt(followedList[stmtNo2]))) {
		result.push_back(followedList[stmtNo2]);
	}
	else {
		result = followedStarList[synonym1][stmtNo2];
	}
	return result;
}

//represents: Follows(_, b) or Follows*(_, b)
vector<unsigned int> PKB::getAllFollowsStmts(string synonym2, bool star)
{
	vector<unsigned int> stmts = getAllStmtsThatFitSynonym(synonym2);
	vector<unsigned int> result;
	copy_if(stmts.begin(), stmts.end(), back_inserter(result), [=](unsigned int stmtNo) {
		return hasFollowedBy(stmtNo, star);
	});
	return result;
}

//represents: Follows(1, b) or Follows*(1, b)
vector<unsigned int> PKB::getAllStmtsThatFollows(unsigned int stmtNo1, string synonym2, bool star)
{
	vector<unsigned int> result;
	if (!star && exactMatch(synonym2, getSynonymTypeOfStmt(followsList[stmtNo1]))) {
		result.push_back(followsList[stmtNo1]);
	}
	else {
		result = followsStarList[synonym2][stmtNo1];
	}
	return result;
}

/****************************************
|										|
|		PKB Parent Relations Query		|
|										|
****************************************/

//represents: Parent(1, 2) or Parent*(1, 2)
bool PKB::isParent(unsigned int stmtNo1, unsigned int stmtNo2, bool star)
{
	return (!star && parentList[stmtNo2] == stmtNo1) ||
		(star && parentStarTable[make_pair(stmtNo1, stmtNo2)]);
}

//represents: Parent(1, _), Parent*(1, _)
bool PKB::hasChild(unsigned int stmtNo1, bool star)
{
	return childList[stmtNo1].size() > 0;
}

//represents: Parent(_, 2) or Parent*(_, 2)
bool PKB::hasParent(unsigned int stmtNo2, bool star)
{
	return parentList[stmtNo2] != 0;
}

//represents: Parent(_, _) or Parent*(_, _)
bool PKB::hasParentPair(bool star)
{
	return parentPairs.size();
}

//represents: Parent(a, b) or Parent*(a, b)
vector<pair<unsigned int, unsigned int>> PKB::getAllParentPair(string synonym1, string synonym2, bool star)
{
	if (star)
		return parentStarPairs[make_pair(synonym1, synonym2)];
	return parentPairs[make_pair(synonym1, synonym2)];
}

//represents: Parent(a, _) or Parent*(a, _)
vector<unsigned int> PKB::getAllParentStmts(string synonym1, bool star)
{
	vector<unsigned int> stmts = getAllStmtsThatFitSynonym(synonym1);
	vector<unsigned int> result;
	copy_if(stmts.begin(), stmts.end(), back_inserter(result), [=](unsigned int stmtNo) {
		return hasChild(stmtNo, star);
	});
	return result;
}

//represents: Parent(a, 2) or Parent*(a, 2)
vector<unsigned int> PKB::getAllStmtsThatIsParentOf(string synonym1, unsigned int stmtNo2, bool star)
{
	vector<unsigned int> result;
	if (!star && exactMatch(synonym1, getSynonymTypeOfStmt(parentList[stmtNo2]))) {
		result.push_back(parentList[stmtNo2]);
	}
	else {
		result = parentStarList[synonym1][stmtNo2];
	}
	return result;
}

//represents: Parent(_, b) or Parent*(_, b)
vector<unsigned int> PKB::getAllChildStmts(string synonym2, bool star)
{
	vector<unsigned int> stmts = getAllStmtsThatFitSynonym(synonym2);
	vector<unsigned int> result;
	copy_if(stmts.begin(), stmts.end(), back_inserter(result), [=](unsigned int stmtNo) {
		return hasParent(stmtNo, star);
	});
	return result;
}

//represents: Parent(1, b) or Parent*(1, b)
vector<unsigned int> PKB::getAllStmtsThatIsChildOf(unsigned int stmtNo1, string synonym2, bool star)
{
	vector<unsigned int> result;
	if (!star) {
		result = childList[stmtNo1];
		remove_if(result.begin(), result.end(), [=](unsigned int stmtNo2) {
			return exactMatch(synonym2, getSynonymTypeOfStmt(stmtNo2));
		});
	}
	else {
		result = childStarList[synonym2][stmtNo1];
	}
	return result;
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
	if (!procedureExists(procName))
		return false;
	return procedureModifiesTable[procName].size() > 0;
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
	for (unsigned int i = 0; i < STATEMENTS.size(); ++i) {
		if (exactMatch(synonym, STATEMENTS[i]))
			return * synonymsList[i];
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

const string PKB::getSynonymTypeOfStmt(unsigned int stmtNo)
{
	for (int index = 1; index < STATEMENTS.size(); ++index)
		if (find(synonymsList[index]->begin(), synonymsList[index]->end(), stmtNo) != synonymsList[index]->end())
			return STATEMENTS[index];
	return STMT_VAR;
}

void PKB::addFollowsPair(unsigned int stmtBefore, unsigned int stmtAfter, bool star)
{
	if (star) {
		followsStarPairs[make_pair(STMT_VAR, STMT_VAR)].push_back(make_pair(stmtBefore, stmtAfter));
		followsStarPairs[make_pair(getSynonymTypeOfStmt(stmtBefore), STMT_VAR)].push_back(make_pair(stmtBefore, stmtAfter));
		followsStarPairs[make_pair(STMT_VAR, getSynonymTypeOfStmt(stmtAfter))].push_back(make_pair(stmtBefore, stmtAfter));
		followsStarPairs[make_pair(getSynonymTypeOfStmt(stmtBefore), getSynonymTypeOfStmt(stmtAfter))].push_back(make_pair(stmtBefore, stmtAfter));
	}
	else {
		followsPairs[make_pair(STMT_VAR, STMT_VAR)].push_back(make_pair(stmtBefore, stmtAfter));
		followsPairs[make_pair(getSynonymTypeOfStmt(stmtBefore), STMT_VAR)].push_back(make_pair(stmtBefore, stmtAfter));
		followsPairs[make_pair(STMT_VAR, getSynonymTypeOfStmt(stmtAfter))].push_back(make_pair(stmtBefore, stmtAfter));
		followsPairs[make_pair(getSynonymTypeOfStmt(stmtBefore), getSynonymTypeOfStmt(stmtAfter))].push_back(make_pair(stmtBefore, stmtAfter));
	}
}

void PKB::addParentPair(unsigned int stmtParent, unsigned int stmtChild, bool star)
{
	if (star) {
		parentStarPairs[make_pair(STMT_VAR, STMT_VAR)].push_back(make_pair(stmtParent, stmtChild));
		parentStarPairs[make_pair(getSynonymTypeOfStmt(stmtParent), STMT_VAR)].push_back(make_pair(stmtParent, stmtChild));
		parentStarPairs[make_pair(STMT_VAR, getSynonymTypeOfStmt(stmtChild))].push_back(make_pair(stmtParent, stmtChild));
		parentStarPairs[make_pair(getSynonymTypeOfStmt(stmtParent), getSynonymTypeOfStmt(stmtChild))].push_back(make_pair(stmtParent, stmtChild));
	}
	else {
		parentPairs[make_pair(STMT_VAR, STMT_VAR)].push_back(make_pair(stmtParent, stmtChild));
		parentPairs[make_pair(getSynonymTypeOfStmt(stmtParent), STMT_VAR)].push_back(make_pair(stmtParent, stmtChild));
		parentPairs[make_pair(STMT_VAR, getSynonymTypeOfStmt(stmtChild))].push_back(make_pair(stmtParent, stmtChild));
		parentPairs[make_pair(getSynonymTypeOfStmt(stmtParent), getSynonymTypeOfStmt(stmtChild))].push_back(make_pair(stmtParent, stmtChild));
	}
}
