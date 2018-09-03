#include "QueryEvaluator.h"

#include <iostream>

using namespace std;

string QueryEvaluator::evaluateQueryTree(QueryTree *queryTree) {
	// logic for evaluating query tree here
	// calling of pkb's api here

	// trasversing query tree - for debugging purpose only pls comment out after debugging
	cout << "===========" << endl;
	cout << "Query Tree" << endl;
	QueryNode *ptr = queryTree->getRoot();
	while (ptr != NULL) {
		cout << ptr->getElement() << endl;
		ptr = ptr->getNext();
	}
	cout << "===========" << endl;

	return "result is result";
}