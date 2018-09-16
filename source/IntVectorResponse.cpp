#include "IntVectorResponse.h"
#include "PKB.h"
#include "Keywords.h"

using namespace keywords::clauseParamType;
using namespace keywords::query;

IntVectorResponse::IntVectorResponse() : APICallResponse() {}

string IntVectorResponse::apiCallForFollows() {
	cout << "Inside intvector follows" << endl;
	vector<int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	if (paramType == make_pair(STMT_NO, SYNONYM) || paramType == make_pair(STMT_NO, UNDERSCORE)) {
		return "getStmtNoThatFollows first param";
		result = PKB::getStmtNoThatFollows(stoi(firstParam), hasTransitiveClosure);
	}	
	else if (paramType == make_pair(SYNONYM, STMT_NO) || paramType == make_pair(UNDERSCORE, STMT_NO)) {
		return "getStmtNoThatIsFollowedBy second param";
		result = PKB::getStmtNoThatIsFollowedBy(stoi(secondParam), hasTransitiveClosure);
	}
	else {
		return "Error in apicallforfollow()";
	}
	return getResults(result);
}

string IntVectorResponse::apiCallForParent() {
	cout << "Inside intvector parent" << endl;
	vector<int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	bool hasTransitiveClosure = suchThatClause.hasTransitiveClosure;

	if (paramType == make_pair(STMT_NO, SYNONYM) || paramType == make_pair(STMT_NO, UNDERSCORE)) {
		return "getStmtNoThatIsChildOf first param";
		result = PKB::getStmtNoThatIsChildOf(stoi(firstParam), hasTransitiveClosure);
	}	
	else if (paramType == make_pair(SYNONYM, STMT_NO) || paramType == make_pair(UNDERSCORE, STMT_NO)) {
		return "getStmtNoThatIsParentOf second param";
		result = PKB::getStmtNoThatIsParentOf(stoi(secondParam), hasTransitiveClosure);
	}
	else {
		return "Error in apicallforparent()";
	}
	return getResults(result);
}

string IntVectorResponse::apiCallForUses() {
	cout << "Inside apiCallForUses" << endl;
	vector<int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string synonymType = synonymTable[firstParam];

	if (paramType == make_pair(SYNONYM, VARIABLE)) {
		if (synonymType == ASSIGNMENT_VAR) {
			return "getAllAssignmentThatUses(secondParam)";
			result = PKB::getAllAssignmentThatUses(secondParam);
		}
		else if (synonymType == STMT_VAR) {
			return "getAllStmtThatUses(secondParam)";
			result = PKB::getAllStmtThatUses(secondParam);
		}
		else if (synonymType == IF_VAR) {
			return "getAllIfThatUses(secondParam)";
			result = PKB::getAllIfThatUses(secondParam);
		}
		else if (synonymType == WHILE_VAR) {
			return "getAllWhileThatUses(secondParam)";
			result = PKB::getAllWhileThatUses(secondParam);
		}
		else if (synonymType == PRINT_VAR) {
			return "getAllPrintThatUses(secondParam)";
			result = PKB::getAllPrintThatUses(secondParam);
		}
		return getResults(result);
	}
	return "Error apiCallForUses()";
}

string IntVectorResponse::apiCallForModifies() {
	cout << "Inside apiCallForModifies" << endl;
	vector<int> result;
	string firstParam = suchThatClause.firstParameter;
	string secondParam = suchThatClause.secondParameter;
	string synonymType = synonymTable[firstParam];

	if (paramType == make_pair(SYNONYM, VARIABLE)) {
		if (synonymType == ASSIGNMENT_VAR) {
			return "getAllAssignmentThatModifies(secondParam)";
			result = PKB::getAllAssignmentThatModifies(secondParam);
		}
		else if (synonymType == STMT_VAR) {
			return "getAllStmtThatModifies(secondParam)";
			result = PKB::getAllStmtThatModifies(secondParam);
		}
		else if (synonymType == IF_VAR) {
			return "getAllIfThatModifies(secondParam)";
			result = PKB::getAllIfThatModifies(secondParam);
		}
		else if (synonymType == WHILE_VAR) {
			return "getAllWhileThatModifies(secondParam)";
			result = PKB::getAllWhileThatModifies(secondParam);
		}
		else if (synonymType == READ_VAR) {
			return "getAllReadThatModifies(secondParam)";
			result = PKB::getAllReadThatModifies(secondParam);
		}
		return getResults(result);
	}
	return "Error apiCallForModifies()";
}

string IntVectorResponse::intVectorToString(vector<int> input) {
	string s = "";
	for (int i : input) {
		s += " " + to_string(i);
	}
	return s;
}

string IntVectorResponse::getResults(vector<int> result) {
	if (!result.empty()) {
		if (!selectSynonymIsFoundInParam()) return getImmediateResults();
		else return intVectorToString(result);
	}
	else return getNoResults();
}