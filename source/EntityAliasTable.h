#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct EntityAliasInfo {
	string aliasName;
	string entityType;
} EntityAliasInfo;

class EntityAliasTable {
public:
	EntityAliasTable();

	int insertEntityAlias(vector<string> entityAliasVector);
	string getEntityTypeFromAlias(string aliasName);
	vector<EntityAliasInfo> getTableData();

private:
	vector<EntityAliasInfo> entityAliasData;
};