#include "IntVectorResponse.h"
#include "PKB.h"
#include "Keywords.h"

using namespace keywords::clauseParamType;
using namespace keywords::query;

IntVectorResponse::IntVectorResponse() : APICallSuchThatClause() {}

vector<string> IntVectorResponse::apiCallForFollows() {
	cout << "Inside intvector follows" << endl;
	vector<int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	if (paramType == make_pair(STMT_NO, SYNONYM) || paramType == make_pair(STMT_NO, UNDERSCORE)) {
		cout << "getStmtNoThatFollows first param" << endl;
		result.push_back(1);
		//result = PKB::getStmtNoThatFollows(stoi(firstParam), hasTransitiveClosure);
	}	
	else if (paramType == make_pair(SYNONYM, STMT_NO) || paramType == make_pair(UNDERSCORE, STMT_NO)) {
		cout << "getStmtNoThatIsFollowedBy second param" << endl;
		result.push_back(1);
		//result = PKB::getStmtNoThatIsFollowedBy(stoi(secondParam), hasTransitiveClosure);
	}
	else {
		return vector<string>();
	}
	return getResults(result);
}

vector<string> IntVectorResponse::apiCallForParent() {
	cout << "Inside intvector parent" << endl;
	vector<int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	if (paramType == make_pair(STMT_NO, SYNONYM) || paramType == make_pair(STMT_NO, UNDERSCORE)) {
		cout << "getStmtNoThatIsChildOf first param" << endl;
		result = PKB::getStmtNoThatIsChildOf(stoi(firstParam), hasTransitiveClosure);
	}	
	else if (paramType == make_pair(SYNONYM, STMT_NO) || paramType == make_pair(UNDERSCORE, STMT_NO)) {
		cout << "getStmtNoThatIsParentOf second param" << endl;
		result = PKB::getStmtNoThatIsParentOf(stoi(secondParam), hasTransitiveClosure);
	}
	else {
		return vector<string>();
	}
	return getResults(result);
}

vector<string> IntVectorResponse::apiCallForUses() {
	cout << "Inside apiCallForUses" << endl;
	vector<int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string synonymType = synonymTable[firstParam];

	if (paramType == make_pair(SYNONYM, VARIABLE)) {
		if (synonymType == ASSIGNMENT_VAR) {
			cout << "getAllAssignmentThatUses(secondParam)" << endl;
			result.push_back(1);
			//result = PKB::getAllAssignmentThatUses(secondParam);
		}
		else if (synonymType == STMT_VAR) {
			cout << "getAllStmtThatUses(secondParam)" << endl;
			result.push_back(1);
			//result = PKB::getAllStmtThatUses(secondParam);
		}
		else if (synonymType == IF_VAR) {
			cout << "getAllIfThatUses(secondParam)" << endl;
			result.push_back(1);
			//result = PKB::getAllIfThatUses(secondParam);
		}
		else if (synonymType == WHILE_VAR) {
			cout << "getAllWhileThatUses(secondParam)" << endl;
			result.push_back(1);
			//result = PKB::getAllWhileThatUses(secondParam);
		}
		else if (synonymType == PRINT_VAR) {
			cout << "getAllPrintThatUses(secondParam)" << endl;
			result.push_back(1);
			//result = PKB::getAllPrintThatUses(secondParam);
		}
		return getResults(result);
	}
	return vector<string>();
}

vector<string> IntVectorResponse::apiCallForModifies() {
	cout << "Inside apiCallForModifies" << endl;
	vector<int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string synonymType = synonymTable[firstParam];

	if (paramType == make_pair(SYNONYM, VARIABLE)) {
		if (synonymType == ASSIGNMENT_VAR) {
			result.push_back(1);
			cout << "getAllAssignmentThatModifies(secondParam)" << endl;
			//result = PKB::getAllAssignmentThatModifies(secondParam);
		}
		else if (synonymType == STMT_VAR) {
			result.push_back(2);
			cout << "getAllStmtThatModifies(secondParam)" << endl;
			//result = PKB::getAllStmtThatModifies(secondParam);
		}
		else if (synonymType == IF_VAR) {
			result.push_back(3);
			cout << "getAllIfThatModifies(secondParam)" << endl;
			//result = PKB::getAllIfThatModifies(secondParam);
		}
		else if (synonymType == WHILE_VAR) {
			result.push_back(4);
			cout << "getAllWhileThatModifies(secondParam)" << endl;
			//result = PKB::getAllWhileThatModifies(secondParam);
		}
		else if (synonymType == READ_VAR) {
			result.push_back(5);
			cout << "getAllReadThatModifies(secondParam)" << endl;
			//result = PKB::getAllReadThatModifies(secondParam);
		}
		return getResults(result);
	}

	return vector<string>();
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