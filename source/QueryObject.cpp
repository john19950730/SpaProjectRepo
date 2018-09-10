#include "QueryObject.h"

using namespace std;

QueryObject::QueryObject() {
	followsClauseIsset = false;
	modifiesClauseIsset = false;
	parentClauseIsset = false;
	selectClauseIsset = false;
	usesClauseIsset = false;
}

QueryObject::QueryObject(STMT_RS_CLAUSE followsClause, STMT_PROC_VAR_RS_CLAUSE modifiesClause,
	STMT_RS_CLAUSE parentClause, SELECT_VAR_CLAUSE selectClause, STMT_PROC_VAR_RS_CLAUSE usesClause) {
	this->setFollowsClause(followsClause);
	this->setModifiesClause(modifiesClause);
	this->setParentClause(parentClause);
	this->setSelectClause(selectClause);
	this->setUsesClause(usesClause);
}

void QueryObject::setFollowsClause(STMT_RS_CLAUSE followsClause) {
	this->FOLLOWS_CLAUSE = followsClause;
	followsClauseIsset = true;
}

void QueryObject::setModifiesClause(STMT_PROC_VAR_RS_CLAUSE modifiesClause) {
	this->MODIFIES_CLAUSE = modifiesClause;
	modifiesClauseIsset = true;
}

void QueryObject::setParentClause(STMT_RS_CLAUSE parentClause) {
	this->PARENT_CLAUSE = parentClause;
	parentClauseIsset = true;
}

void QueryObject::setSelectClause(SELECT_VAR_CLAUSE selectClause) {
	this->SELECT_CLAUSE = selectClause;
	selectClauseIsset = true;
}

void QueryObject::setUsesClause(STMT_PROC_VAR_RS_CLAUSE usesClause) {
	this->USES_CLAUSE = usesClause;
	usesClauseIsset = true;
}

STMT_RS_CLAUSE QueryObject::getFollowsClause() {
	return FOLLOWS_CLAUSE;
}

STMT_PROC_VAR_RS_CLAUSE QueryObject::getModifiesClause() {
	return MODIFIES_CLAUSE;
}

STMT_RS_CLAUSE QueryObject::getParentClause() {
	return PARENT_CLAUSE;
}

SELECT_VAR_CLAUSE QueryObject::getSelectClause() {
	return SELECT_CLAUSE;
}

STMT_PROC_VAR_RS_CLAUSE QueryObject::getUsesClause() {
	return USES_CLAUSE;
}

bool QueryObject::hasClauses() {
	if (modifiesClauseIsset && usesClauseIsset && followsClauseIsset && parentClauseIsset)
		return false;
	return true;
}

bool QueryObject::hasFollowsClause() {
	if (followsClauseIsset) return false;
	return true;
}

bool QueryObject::hasModifiesClause() {
	if (modifiesClauseIsset) return false;
	return true;
}

bool QueryObject::hasParentClause() {
	if (parentClauseIsset) return false;
	return true;
}

bool QueryObject::hasUsesClause() {
	if (usesClauseIsset) return false;
	return true;
}

int QueryObject::getNumberOfClauses() {
	int count = 0;

	if (hasUsesClause()) count++;
	if (hasModifiesClause()) count++;
	if (hasParentClause()) count++;
	if (hasFollowsClause()) count++;

	return count;
}