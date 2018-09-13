#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
typedef short PROC;

template <typename T>
class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
public:
	// SPA relationships table
	static void addFollows(int stmtBefore, int stmtAfter);
	static void addParent(int stmtParent, int stmtChild);
	static void addUses(int stmtNo, string varName);
	static void addModifies(int stmtNo, string varName);

	// SPA synonyms table
	static int addVariable(string varName);
	static int addAssign(int stmtNo);
	static int addRead(int stmtNo);
	static int addPrint(int stmtNo);
	static int addIf(int stmtNo);
	static int addWhile(int stmtNo);
	static int addProcedure(string procName, pair<int, int> startEndLine);

	// SPA relationships query
	static bool isFollows(int stmtNo1, int stmtNo2, bool star);
	static bool isParent(int stmtNo1, int stmtNo2, bool star);
	static bool isUses(int stmtNo1, string varName);
	static bool isModifies(int stmtNo1, string varName);
	
	// SPA advanced Uses query
	static vector<int> getAllStmtThatUses(string varName);
	static vector<int> getAllAssignmentThatUses(string varName);
	static vector<int> getAllPrintThatUses(string varName);
	static vector<int> getAllIfThatUses(string varName);
	static vector<int> getAllWhileThatUses(string varName);
	static vector<string> getAllProcedureThatUses(string varName);

	// SPA Uses Pair query
	static vector< pair<int, string> > getAllAssignmentUsesVariablePairs();
	static vector< pair<int, string> > getAllStmtUsesVariablePairs();
	static vector< pair<string, string> > getAllProcedureUsesVariablePairs();

	// SPA advanced Modifies query
	static vector<int> getAllStmtThatModifies(string varName);
	static vector<int> getAllAssignmentThatModifies(string varName);
	static vector<int> getAllReadThatModifies(string varName);
	static vector<int> getAllIfThatModifies(string varName);
	static vector<int> getAllWhileThatModifies(string varName);
	static vector<string> getAllProcedureThatModifies(string varName);

	// SPA Modifies Pair query
	static vector< pair<int, string> > getAllAssignmentModifiesVariablePairs();
	static vector< pair<int, string> > getAllStmtModifiesVariablePairs();
	static vector< pair<string, string> > getAllProcedureModifiesVariablePairs();

	// SPA synonyms query
	static vector<string> getVariables();
	static vector<int> getAssigns();
	static vector<int> getReads();
	static vector<int> getPrints();
	static vector<int> getIfs();
	static vector<int> getWhiles();
	static vector< pair<string, pair<int, int> > > getProcedures();
};
