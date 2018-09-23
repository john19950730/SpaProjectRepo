#include "QueryNode.h"

#include <string>

using namespace std;

QueryNode::QueryNode(string element) {
	this->element = element;
	this->nextPtr = NULL;
}
QueryNode::QueryNode(string element, QueryNode *nextNode) {
	this->element = element;
	this->nextPtr = nextNode;
}
void QueryNode::setNext(QueryNode *nextNode) {
	this->nextPtr = nextNode;
}
QueryNode* QueryNode::getNext() {
	return nextPtr;
}
string QueryNode::getElement() {
	return element;
}