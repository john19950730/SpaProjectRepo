#pragma once
#include <string>

using namespace std;

class QueryNode {
private:
	string element;
	QueryNode *nextPtr;
public:
	QueryNode(string element);
	QueryNode(string element, QueryNode *nextNode);
	void setNext(QueryNode *nextNode);
	QueryNode* getNext();
	string getElement();
};