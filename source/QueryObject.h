#pragma once
#include "QueryObjStructures.h"
#include <string>

using namespace std;

class QueryObject {
private:
	SELECT_VAR_CLAUSE *SELECT_CLAUSE = NULL;
	STMT_PROC_VAR_RS_CLAUSE *MODIFIES_CLAUSE = NULL;
	STMT_PROC_VAR_RS_CLAUSE *USES_CLAUSE = NULL;
	STMT_RS_CLAUSE *FOLLOWS_CLAUSE = NULL;
	STMT_RS_CLAUSE *PARENT_CLAUSE = NULL;
public:
	// Constructors
	QueryObject();
	QueryObject(STMT_RS_CLAUSE *followsClause, STMT_PROC_VAR_RS_CLAUSE *modifiesClause, STMT_RS_CLAUSE *parentClause,
		SELECT_VAR_CLAUSE *selectClause, STMT_PROC_VAR_RS_CLAUSE *usesClause);

	// Setter methods
	void setSelectClause(SELECT_VAR_CLAUSE *selectClause);
	void setModifiesClause(STMT_PROC_VAR_RS_CLAUSE *modifiesClause);
	void setUsesClause(STMT_PROC_VAR_RS_CLAUSE *usesClause);
	void setFollowsClause(STMT_RS_CLAUSE *followsClause);
	void setParentClause(STMT_RS_CLAUSE *parentClause);

	// Getter methods
	SELECT_VAR_CLAUSE* getSelectClause();
	STMT_PROC_VAR_RS_CLAUSE* getModifiesClause();
	STMT_PROC_VAR_RS_CLAUSE* getUsesClause();
	STMT_RS_CLAUSE* getFollowsClause();
	STMT_RS_CLAUSE* getParentClause();

	// Checking methods
	bool hasClauses();
	bool hasModifiesClause();
	bool hasUsesClause();
	bool hasFollowsClause();
	bool hasParentClause();

	// Counting methods
	int getNumberOfClauses();
};