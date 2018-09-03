#include "EntityAliasTable.h"

EntityAliasTable::EntityAliasTable()
{
	entityAliasData = {};
}

int EntityAliasTable::insertEntityAlias(vector<string> entityAliasVector)
{
	string aliasName = entityAliasVector[1];
	string entityType = entityAliasVector[0];
	EntityAliasInfo entityAliasInfo = { aliasName , entityType };
	entityAliasData.push_back(entityAliasInfo);

	return entityAliasData.size() - 1;
}

vector<EntityAliasInfo> EntityAliasTable::getTableData()
{
	return entityAliasData;
}
