#pragma once
#include "QueryNode.h"

#include <string>
#include <vector>

using namespace std;

class QueryTree {
private:
	QueryNode *rootPtr; // points to first queryNode (pass in the address of the first queryNode
	//QueryNode *resultPtr; // points to the result node
	//QueryNode *suchThatPtr; // points to the such that node
public:
	QueryTree(QueryNode *firstNode);
	void addResultNode(QueryNode *resultNode);
	QueryNode* getRoot();
};