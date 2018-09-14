#include "QueryObject.h"

using namespace std;

QueryObject::QueryObject() {
	followsClauseIsset = false;
	modifiesClauseIsset = false;
	parentClauseIsset = false;
	selectClauseIsset = false;
	usesClauseIsset = false;
}

QueryObject::QueryObject(vector<string> selectClause, vector<SUCH_THAT_CLAUSE> followsClause,
	vector<SUCH_THAT_CLAUSE> modifiesClause, vector<SUCH_THAT_CLAUSE> parentClause, 
	vector<SUCH_THAT_CLAUSE> usesClause) {
	this->setFollowsClause(followsClause);
	this->setModifiesClause(modifiesClause);
	this->setParentClause(parentClause);
	this->setSelectClause(selectClause);
	this->setUsesClause(usesClause);
}

void QueryObject::setFollowsClause(vector<SUCH_THAT_CLAUSE> followsClause) {
	this->followsClause = followsClause;
	followsClauseIsset = true;
}

void QueryObject::setModifiesClause(vector<SUCH_THAT_CLAUSE> modifiesClause) {
	this->modifiesClause = modifiesClause;
	modifiesClauseIsset = true;
}

void QueryObject::setParentClause(vector<SUCH_THAT_CLAUSE> parentClause) {
	this->parentClause = parentClause;
	parentClauseIsset = true;
}

void QueryObject::setSelectClause(vector<string> selectClause) {
	this->selectSynoymsClause = selectClause;
	selectClauseIsset = true;
}

void QueryObject::setUsesClause(vector<SUCH_THAT_CLAUSE> usesClause) {
	this->usesClause = usesClause;
	usesClauseIsset = true;
}

void QueryObject::setSynonymTable(map<string, string> synonymTable) {
	this->synonymTable = synonymTable;
}

vector<SUCH_THAT_CLAUSE> QueryObject::getFollowsClause() {
	return followsClause;
}

vector<SUCH_THAT_CLAUSE> QueryObject::getModifiesClause() {
	return modifiesClause;
}

vector<SUCH_THAT_CLAUSE> QueryObject::getParentClause() {
	return parentClause;
}

vector<string> QueryObject::getSelectClause() {
	return selectSynoymsClause;
}

vector<SUCH_THAT_CLAUSE> QueryObject::getUsesClause() {
	return usesClause;
}

map<string, string> QueryObject::getSynonymTable() {
	return synonymTable;
}

bool QueryObject::hasClauses() {
	if (!modifiesClauseIsset && !usesClauseIsset && !followsClauseIsset && !parentClauseIsset)
		return false;
	return true;
}

bool QueryObject::hasFollowsClause() {
	return followsClauseIsset;
}

bool QueryObject::hasModifiesClause() {
	return modifiesClauseIsset;
}

bool QueryObject::hasParentClause() {
	return parentClauseIsset;
}

bool QueryObject::hasUsesClause() {
	return usesClauseIsset;
}

// Changes to be made in iteration 2
int QueryObject::getNumberOfClauses() {
	int count = 0;

	if (hasUsesClause()) count++;
	if (hasModifiesClause()) count++;
	if (hasParentClause()) count++;
	if (hasFollowsClause()) count++;

	return count;
}