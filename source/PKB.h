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

class PKB {
public:
	// FOR FRONT-END
	/* SPA relationships table */
	static void addFollows(unsigned int stmtBefore, unsigned int stmtAfter);
	static void addParent(unsigned int stmtParent, unsigned int stmtChild);
	static void addUses(unsigned int stmtNo, string varName);
	static void addProcedureUses(string procName, string varName);
	static void addModifies(unsigned int stmtNo, string varName);
	static void addProcedureModifies(string procName, string varName);

	/* SPA synonyms table */
	static unsigned int addVariable(string varName);
	static unsigned int addAssign(unsigned int stmtNo);
	static unsigned int addIf(unsigned int stmtNo);
	static unsigned int addWhile(unsigned int stmtNo);
	static unsigned int addRead(unsigned int stmtNo);
	static unsigned int addPrint(unsigned int stmtNo);
	static unsigned int addCall(unsigned int stmtNo);
	static unsigned int addProcedure(string procName);

	// FOR PQL
	/* SPA Follows Relations query */
	static bool isFollows(unsigned int stmtNo1, unsigned int stmtNo2, bool star); // Follows(1, 2)
	static bool hasFollows(unsigned int stmtNo1, bool star); // Follows(1, _)
	static bool hasFollowedBy(unsigned int stmtNo2, bool star); // Follows(_, 2)
	static bool hasFollowsPair(bool star); // Follows(_, _)
	static vector<pair<unsigned int, unsigned int> > getAllFollowsPair(string synonym1, string synonym2, bool star); // Follows(a, b)
	static vector<unsigned int> getAllFollowedStmts(string synonym1, bool star); // Follows(a, _)
	static vector<unsigned int> getAllStmtsFollowedBy(string synonym1, unsigned int stmtNo2, bool star); // Follows(a, 2)
	static vector<unsigned int> getAllFollowsStmts(string synonym2, bool star); // Follows(_, b)
	static vector<unsigned int> getAllStmtsThatFollows(unsigned int stmtNo1, string synonym2, bool star); // Follows(1, b)

	/* SPA Parent Relations query */
	static bool isParent(unsigned int stmtNo1, unsigned int stmtNo2, bool star); // Parent(1, 2)
	static bool hasChild(unsigned int stmtNo1, bool star); // Parent(1, _)
	static bool hasParent(unsigned int stmtNo2, bool star); // Parent(_, 2)
	static bool hasParentPair(bool star); // Parent(_, _)
	static vector<pair<unsigned int, unsigned int> > getAllParentPair(string synonym1, string synonym2, bool star); // Parent(a, b)
	static vector<unsigned int> getAllParentStmts(string synonym1, bool star); // Parent(a, _)
	static vector<unsigned int> getAllStmtsThatIsParentOf(string synonym1, unsigned int stmtNo2, bool star); // Parent(a, 2)
	static vector<unsigned int> getAllChildStmts(string synonym2, bool star); // Parent(_, b)
	static vector<unsigned int> getAllStmtsThatIsChildOf(unsigned int stmtNo1, string synonym2, bool star); // Parent(1, b)

	/* SPA Uses Relations Query */
	static bool isUses(unsigned int stmtNo1, string varName); // Uses(1, "var")
	static bool hasUses(unsigned int stmtNo1); // Uses(1, _)
	static vector<string> getAllVariablesUsedByStmtNo(unsigned int stmtNo); // Uses(1, v)
	static vector<unsigned int> getAllStmtsThatUsesVariable(string synonym, string varName); // Uses(a, "var")
	static vector<unsigned int> getAllStmtsThatUses(string synonym); //Uses(a, _)
	static vector< pair<unsigned int, string> > getAllStmtUsesVariablePairs(string synonym); // Uses(a, v)
	static bool isProcedureUses(string procName, string varName); // Uses("proc", "var")
	static bool hasProcedureUses(string procName); // Uses("proc", _)
	static vector<string> getAllVariablesUsedByProcedure(string procName); // Uses("proc" , v)
	static vector<string> getAllProceduresThatUsesVariable(string varName); // Uses(p, "var")
	static vector<string> getAllProceduresThatUses(); // Uses(p, _)
	static vector< pair<string, string> > getAllProcedureUsesVariablePairs(); // Uses(p, v)

	/* SPA Modifies Relations Query */
	static bool isModifies(unsigned int stmtNo1, string varName); // Modifies(1, "var")
	static bool hasModifies(unsigned int stmtNo1); // Modifies(1, _)
	static vector<string> getAllVariablesModifiedByStmtNo(unsigned int stmtNo); // Modifies(1, v)
	static vector<unsigned int> getAllStmtThatModifiesVariable(string synonym, string varName); // Modifies(a, "var")
	static vector<unsigned int> getAllStmtThatModifies(string synonym); // Modifies(a, _)
	static vector< pair<unsigned int, string> > getAllStmtModifiesVariablePairs(string synonym); // Modifies(a, v)
	static bool isProcedureModifies(string procName, string varName); // Modifies("proc", "var")
	static bool hasProcedureModifies(string procName); // Modifies("proc", _)
	static vector<string> getAllVariablesModifiedByProcedure(string procName); // Modifies("proc", v)
	static vector<string> getAllProceduresThatModifiesVariable(string varName); // Modifies(p, "var")
	static vector<string> getAllProceduresThatModifies(); // Modifies(p, _)
	static vector< pair<string, string> > getAllProcedureModifiesVariablePairs(); // Modifies(p, v)

	// PKB pattern query
	static vector<unsigned int> getAllAssignsWithConstant(string constant);
	static bool hasAssignmentStmt(); // a(_, _)
	static bool isAssignmentUsesConstant(unsigned int stmtNo, string constant);

	// PKB synonyms query
	static vector<string> getVariables();
	static vector<unsigned int> getAllStmts();
	static vector<unsigned int> getAssigns();
	static vector<unsigned int> getIfs();
	static vector<unsigned int> getWhiles();
	static vector<unsigned int> getReads();
	static vector<unsigned int> getPrints();
	static vector<unsigned int> getCalls();
	static vector<string> getProcedureNames();
	static vector<unsigned int> getAllStmtsThatFitSynonym(string synonym);

private:
	static unsigned int addStatement(unsigned int stmtNo);
	static bool procedureExists(string procName);
	static bool exactMatch(string s1, string s2);
	static string getSynonymTypeOfStmt(unsigned int stmtNo);
	static void addFollowsPair(unsigned int stmtBefore, unsigned int stmtAfter, bool star);
};
