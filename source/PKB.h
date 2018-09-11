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
	static int addProcedure(string procName);

	// SPA relationships query
	static bool isFollows(int stmtNo1, int stmtNo2, bool star);
	static bool isParent(int stmtNo1, int stmtNo2, bool star);
	static bool isUses(int stmtNo1, string varName);
	static bool isModifies(int stmtNo1, string varName);
	
	// SPA advanced Uses query
	static vector<int> getAllStmtThatUses(string v);
	static vector<int> getAllAssignmentThatUses(string v);


	// SPA advanced Modifies query
	static vector<int> getAllStmtThatModifies(string v);
	static vector<int> getAllAssignmentThatModifies(string v);

	// SPA synonyms query
	static vector<string> getVariables();
	static vector<int> getAssigns();
	static vector<int> getReads();
	static vector<int> getPrints();
	static vector<int> getIfs();
	static vector<int> getWhiles();
	static vector<string> getProcedures();
};
