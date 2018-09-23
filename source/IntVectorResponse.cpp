#include "IntVectorResponse.h"
#include "PKB.h"
#include "Keywords.h"

using namespace keywords::clauseParamType;
using namespace keywords::query;

IntVectorResponse::IntVectorResponse() : APICallSuchThatClause() {}

IntVectorResult* IntVectorResponse::apiCallForFollows() {
	cout << "Inside intvector follows" << endl;
	vector<unsigned int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;
	string synonym;

	if (paramType == make_pair(SYNONYM, STMT_NO)) {
		result = PKB::getAllStmtsFollowedBy(synonymTable[firstParam], unsigned(stoi(secondParam)), hasTransitiveClosure); 
		synonym = firstParam;
		cout << "getAllStmtsFollowedBy // Follows(a, 2)" << endl;
	}
	else if (paramType == make_pair(STMT_NO, SYNONYM)) {
		result = PKB::getAllStmtsThatFollows(unsigned(stoi(firstParam)), synonymTable[secondParam], hasTransitiveClosure); 
		synonym = secondParam;
		cout << "getAllStmtsThatFollows // Follows(1, b)" << endl;
	}
	else if (paramType == make_pair(UNDERSCORE, SYNONYM)) {
		result = PKB::getAllFollowsStmts(synonymTable[secondParam], hasTransitiveClosure); // Follows(_, b)
		synonym = secondParam;
		cout << "getAllFollowsStmts // Follows(_, b)" << endl;
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		result = PKB::getAllFollowedStmts(synonymTable[firstParam], hasTransitiveClosure); // Follows(a, _)
		synonym = firstParam;
		cout << "getAllFollowedStmts // Follows(a, _)" << endl;
	}

	IntVectorResult* intVectorResult = new IntVectorResult(result, synonym);
	return intVectorResult;
}

IntVectorResult* IntVectorResponse::apiCallForParent() {
	cout << "Inside intvector parent" << endl;
	vector<unsigned int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;
	string synonym;
	
	if (paramType == make_pair(SYNONYM, STMT_NO)) {
		result = PKB::getAllStmtsThatIsParentOf(synonymTable[firstParam], unsigned(stoi(secondParam)), hasTransitiveClosure); 
		synonym = firstParam;
		cout << "getAllStmtsThatIsParentOf // Parent(a, 2)" << endl;
	}
	else if (paramType == make_pair(STMT_NO, SYNONYM)) {
		result = PKB::getAllStmtsThatIsChildOf(unsigned(stoi(firstParam)), synonymTable[secondParam], hasTransitiveClosure); 
		synonym = secondParam;
		cout << "getAllStmtsThatIsChildOf // Parent(1, b)" << endl;
	}
	else if (paramType == make_pair(UNDERSCORE, SYNONYM)) {
		result = PKB::getAllChildStmts(synonymTable[secondParam], hasTransitiveClosure); 
		synonym = secondParam;
		cout << "getAllChildStmts // Parent(_, b)" << endl;
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		result = PKB::getAllParentStmts(synonymTable[firstParam], hasTransitiveClosure); // Parent(a, _)
		synonym = firstParam;
		cout << "getAllParentStmts // Parent(a, _)" << endl;
	}

	IntVectorResult* intVectorResult = new IntVectorResult(result, synonym);
	return intVectorResult;
}

IntVectorResult* IntVectorResponse::apiCallForUses() {
	cout << "Inside apiCallForUses" << endl;
	vector<unsigned int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string synonymType = synonymTable[firstParam];
	string synonym;

	if (paramType == make_pair(SYNONYM, VARIABLE)) {
		result = PKB::getAllStmtsThatUsesVariable(synonymType, secondParam);
		synonym = firstParam;
	
		cout << " PKB::getAllStmtsThatUsesVariable(synonymType, secondParam); // Uses(a, 'var')" << endl;
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		result = PKB::getAllStmtsThatUses(synonymType);
		synonym = firstParam;

		cout << "PKB::getAllStmtsThatUses(synonymType);	//Uses(a, _)" << endl;
	}

	IntVectorResult* intVectorResult = new IntVectorResult(result, synonym);
	return intVectorResult;
}

IntVectorResult* IntVectorResponse::apiCallForModifies() {
	cout << "Inside apiCallForModifies" << endl;
	vector<unsigned int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string synonymType = synonymTable[firstParam];
	string synonym;

	if (paramType == make_pair(SYNONYM, VARIABLE)) {
		result = PKB::getAllStmtThatModifiesVariable(synonymType, secondParam);
		synonym = firstParam;
		
		cout << "PKB::getAllStmtThatModifiesVariable(synonymType, secondParam); // Modifies(a, 'var')" << endl;
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		result = PKB::getAllStmtThatModifies(synonymType);
		synonym = firstParam;

		cout << "PKB::getAllStmtThatModifies(synonymType);	// Modifies(a, _)" << endl;
	}

	IntVectorResult* intVectorResult = new IntVectorResult(result, synonym);
	return intVectorResult;
}