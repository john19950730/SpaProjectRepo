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
	static void addFollows(unsigned int stmtBefore, unsigned int stmtAfter);
	static void addParent(unsigned int stmtParent, unsigned int stmtChild);
	static void addUses(unsigned int stmtNo, string varName);
	static void addModifies(unsigned int stmtNo, string varName);

	// SPA synonyms table
	static int addVariable(string varName);
	static int addAssign(unsigned int stmtNo);
	static int addRead(unsigned int stmtNo);
	static int addPrint(unsigned int stmtNo);
	static int addIf(unsigned int stmtNo);
	static int addWhile(unsigned int stmtNo);
	static int addProcedure(string procName, pair<unsigned int, unsigned int> startEndLine);

	// SPA basic relationships query
	static bool isFollows(unsigned int stmtNo1, unsigned int stmtNo2, bool star);
	static bool isParent(unsigned int stmtNo1, unsigned int stmtNo2, bool star);
	static bool isUses(unsigned int stmtNo1, string varName);
	static bool isModifies(unsigned int stmtNo1, string varName);

	// SPA advanced Follows query
	static vector< pair<int, int> > getAllFollowsPair(bool star);
	static vector<int> getStmtNoThatFollows(int stmtNo, bool star);
	static vector<int> getStmtNoThatIsFollowedBy(int stmtNo, bool star);

	// SPA advanced Parent query
	static vector< pair<int, int> > getAllParentPair(bool star);
	static vector<int> getStmtNoThatIsChildOf(int stmtNo, bool star);
	static vector<int> getStmtNoThatIsParentOf(int stmtNo, bool star);

	// SPA Uses(a, "b") query
	static vector<unsigned int> getAllStmtThatUses(char synonym, string varName);
	static vector<string> getAllProcedureThatUses(string varName);

	// SPA Uses(a, b) query
	static vector< pair<int, string> > getAllAssignmentUsesVariablePairs();
	static vector< pair<int, string> > getAllStmtUsesVariablePairs();
	static vector< pair<string, string> > getAllProcedureUsesVariablePairs();

	// SPA Uses(stmtNo/procName, b) query
	static vector<string> getAllVariablesUsedByStmtNo(unsigned int stmtNo);
	static vector<string> getAllVariablesUsedByProcedures(string procName);

	// SPA Modifies(a, "b") query
	static vector<int> getAllStmtThatModifies(string varName);
	static vector<int> getAllAssignmentThatModifies(string varName);
	static vector<int> getAllReadThatModifies(string varName);
	static vector<int> getAllIfThatModifies(string varName);
	static vector<int> getAllWhileThatModifies(string varName);
	static vector<string> getAllProcedureThatModifies(string varName);

	// SPA Modifies(a, b) query
	static vector< pair<int, string> > getAllAssignmentModifiesVariablePairs();
	static vector< pair<int, string> > getAllStmtModifiesVariablePairs();
	static vector< pair<string, string> > getAllProcedureModifiesVariablePairs();

	// SPA Modifies(stmtNo/procName, b) query
	static vector<string> getAllVariablesModifiedByStmtNo(unsigned int stmtNo);
	static vector<string> getAllVariablesModifiedByProcedures(string procName);

	// SPA synonyms query
	static vector<string> getVariables();
	static vector<unsigned int> getAssigns();
	static vector<unsigned int> getReads();
	static vector<unsigned int> getPrints();
	static vector<unsigned int> getIfs();
	static vector<unsigned int> getWhiles();
	static unordered_map<string, pair<unsigned int, unsigned int> > getProcedures();
	static vector<string> getProcedureNames();

private:
	static vector<unsigned int> getAllStmts();
	static vector<unsigned int> getAllStmtsThatFitSynonnym(char synonym);
};
