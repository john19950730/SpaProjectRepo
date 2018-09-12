#pragma once
#include "QueryObjStructures.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class QueryObject {
private:
	vector<string> selectSynoymsClause;
	vector<SUCH_THAT_CLAUSE> selectClause;
	vector<SUCH_THAT_CLAUSE> modifiesClause;
	vector<SUCH_THAT_CLAUSE> usesClause;
	vector<SUCH_THAT_CLAUSE> followsClause;
	vector<SUCH_THAT_CLAUSE> parentClause;
	map<string, string> entityAliases;

	bool selectClauseIsset;
	bool modifiesClauseIsset;
	bool usesClauseIsset;
	bool followsClauseIsset;
	bool parentClauseIsset;
public:
	// Constructors
	QueryObject();
	QueryObject(vector<string> selectClause, vector<SUCH_THAT_CLAUSE> followsClause, vector<SUCH_THAT_CLAUSE> modifiesClause,
		vector<SUCH_THAT_CLAUSE> parentClause, vector<SUCH_THAT_CLAUSE> usesClause);

	// Setter methods
	void setSelectClause(vector<string> selectClause);
	void setModifiesClause(vector<SUCH_THAT_CLAUSE> modifiesClause);
	void setUsesClause(vector<SUCH_THAT_CLAUSE> usesClause);
	void setFollowsClause(vector<SUCH_THAT_CLAUSE> followsClause);
	void setParentClause(vector<SUCH_THAT_CLAUSE> parentClause);
	void setEntityAliasMap(map<string, string> entityAliases);

	// Getter methods
	vector<string> getSelectClause();
	vector<SUCH_THAT_CLAUSE> getModifiesClause();
	vector<SUCH_THAT_CLAUSE> getUsesClause();
	vector<SUCH_THAT_CLAUSE> getFollowsClause();
	vector<SUCH_THAT_CLAUSE> getParentClause();
	map<string, string> getEntityAliases();

	// Checking methods
	bool hasClauses();
	bool hasModifiesClause();
	bool hasUsesClause();
	bool hasFollowsClause();
	bool hasParentClause();

	// Counting methods
	int getNumberOfClauses();
};