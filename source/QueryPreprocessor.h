#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef short PROC;

class RefTable;

class QueryPreprocessor {
public:
	static RefTable* varTable;
	static bool validateQuery(std::string query);

};