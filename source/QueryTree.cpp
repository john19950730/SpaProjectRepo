#include "QueryTree.h"
#include "QueryNode.h"

#include <string>
#include <vector>

QueryTree::QueryTree(QueryNode *firstNode) {
	rootPtr = firstNode; // rootptr = address of the first node
	
}
void QueryTree::addResultNode(QueryNode *resultNode) {
	// create a new result node called "result", where its nextPtr points to the resultNode
	QueryNode *newNode = new QueryNode("result", resultNode);
	rootPtr->setNext(newNode);
}
QueryNode* QueryTree::getRoot() {
	return rootPtr;
}