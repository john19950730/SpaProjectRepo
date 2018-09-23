#include "IntVectorResponse.h"
#include "PKB.h"
#include "Keywords.h"

using namespace keywords::clauseParamType;
using namespace keywords::query;

IntVectorResponse::IntVectorResponse() : APICallSuchThatClause() {}

vector<string> IntVectorResponse::apiCallForFollows() {
	cout << "Inside intvector follows" << endl;
	vector<unsigned int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;
	string forTesting;
	vector<string> results;

	if (paramType == make_pair(SYNONYM, STMT_NO)) {
		//result = PKB::getAllStmtsFollowedBy(synonymTable[firstParam], unsigned(stoi(secondParam)), hasTransitiveClosure); 
		forTesting = "getAllStmtsFollowedBy // Follows(a, 2)";
	}
	else if (paramType == make_pair(STMT_NO, SYNONYM)) {
		//result = PKB::getAllStmtsThatFollows(unsigned(stoi(firstParam)), synonymTable[secondParam], hasTransitiveClosure); 
		forTesting = "getAllStmtsThatFollows // Follows(1, b)";
	}
	else if (paramType == make_pair(UNDERSCORE, SYNONYM)) {
		//result = PKB::getAllFollowsStmts(synonymTable[secondParam], hasTransitiveClosure); // Follows(_, b)
		forTesting = "getAllFollowsStmts // Follows(_, b)";
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		//result = PKB::getAllFollowedStmts(synonymTable[firstParam], hasTransitiveClosure); // Follows(a, _)
		forTesting = "getAllFollowedStmts // Follows(a, _)";
	}

	results.push_back(forTesting);
	return results;
}

vector<string> IntVectorResponse::apiCallForParent() {
	cout << "Inside intvector parent" << endl;
	vector<unsigned int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;
	string forTesting;
	vector<string> results;
	
	if (paramType == make_pair(SYNONYM, STMT_NO)) {
		//result = PKB::getAllStmtsThatIsParentOf(synonymTable[firstParam], unsigned(stoi(secondParam)), hasTransitiveClosure); 
		forTesting = "getAllStmtsThatIsParentOf // Parent(a, 2)";
	}
	else if (paramType == make_pair(STMT_NO, SYNONYM)) {
		//result = PKB::getAllStmtsThatIsChildOf(unsigned(stoi(firstParam)), synonymTable[secondParam], hasTransitiveClosure); 
		forTesting = "getAllStmtsThatIsChildOf // Parent(1, b)";
	}
	else if (paramType == make_pair(UNDERSCORE, SYNONYM)) {
		//result = PKB::getAllChildStmts(synonymTable[secondParam], hasTransitiveClosure); 
		forTesting = "getAllChildStmts // Parent(_, b)";
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		//result = PKB::getAllParentStmts(synonymTable[firstParam], hasTransitiveClosure); // Parent(a, _)
		forTesting = "getAllParentStmts // Parent(a, _)";
	}

	results.push_back(forTesting);
	return results;
}

vector<string> IntVectorResponse::apiCallForUses() {
	cout << "Inside apiCallForUses" << endl;
	vector<unsigned int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string synonymType = synonymTable[firstParam];
	string forTesting;
	vector<string> results;

	if (paramType == make_pair(SYNONYM, VARIABLE)) {
		//result = PKB::getAllStmtsThatUsesVariable(synonymType, secondParam);
		forTesting = " PKB::getAllStmtsThatUsesVariable(synonymType, secondParam); // Uses(a, 'var')";
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		//result = PKB::getAllStmtsThatUses(synonymType);
		forTesting = "PKB::getAllStmtsThatUses(synonymType);	//Uses(a, _)";
	}

	results.push_back(forTesting);
	return results;
}

vector<string> IntVectorResponse::apiCallForModifies() {
	cout << "Inside apiCallForModifies" << endl;
	vector<unsigned int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string synonymType = synonymTable[firstParam];
	string forTesting; 
	vector<string> results;

	if (paramType == make_pair(SYNONYM, VARIABLE)) {
		//result = PKB::getAllStmtThatModifiesVariable(synonymType, secondParam);
		forTesting = "PKB::getAllStmtThatModifiesVariable(synonymType, secondParam); // Modifies(a, 'var')";
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE)) {
		//result = PKB::getAllStmtThatModifies(synonymType);
		forTesting = "PKB::getAllStmtThatModifies(synonymType);	// Modifies(a, _)";
	}

	results.push_back(forTesting);
	return results;
}

string IntVectorResponse::intVectorToString(vector<int> input) {
	string s = "";
	for (int i : input) {
		s += " " + to_string(i);
	}
	return s;
}

vector<string> IntVectorResponse::getResults(vector<int> result) {
	if (!result.empty()) {
		if (!selectSynonymIsFoundInParam()) return getImmediateResults();
		//else return intVectorToString(result);
		else return convertVectorIntToVectorStr(result);
	}
	else return getNoResults();
}

vector<string> IntVectorResponse::convertVectorIntToVectorStr(vector<int> input) {
	vector<string> strVector;
	for (int i : input) {
		strVector.push_back(to_string(i));
	}
	return strVector;
}