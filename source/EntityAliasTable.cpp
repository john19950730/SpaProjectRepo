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
	// wip - currently does not check for duplicates
	entityAliasData.push_back(entityAliasInfo);

	return entityAliasData.size() - 1;
}

string EntityAliasTable::getEntityTypeFromAlias(string aliasName)
{
	for (EntityAliasInfo info : entityAliasData) {
		if (info.aliasName == aliasName)
			return info.entityType;
	}
	return "";
}

vector<EntityAliasInfo> EntityAliasTable::getTableData()
{
	return entityAliasData;
}
