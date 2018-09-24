#include "APICallPatternClause.h"
#include "Keywords.h"
#include "PKB.h"

using namespace keywords::query;
using namespace keywords::clauseParamType;

APICallPatternClause::APICallPatternClause(pair<string, string> paramType, PATTERN_CLAUSE patternClause, string selectSynonym, map<string, string> synonymTable) {
	this->patternClause = patternClause;
	this->setParamType(paramType);
	this->setSelectSynonym(selectSynonym);
	this->setSynonymTable(synonymTable);
}

Result* APICallPatternClause::executeApiCall() {
	if (paramType == make_pair(VARIABLE, UNDERSCORE) || paramType == make_pair(UNDERSCORE, CONSTANT) || paramType == make_pair(UNDERSCORE, VARIABLE)
		|| paramType == make_pair(VARIABLE, CONSTANT) || paramType == make_pair(VARIABLE, VARIABLE) || paramType == make_pair(UNDERSCORE, UNDERSCORE)) {
		return getIntVectorResponse();
	}
	else if (paramType == make_pair(SYNONYM, UNDERSCORE) || paramType == make_pair(SYNONYM, CONSTANT)
		|| paramType == make_pair(SYNONYM, VARIABLE)) {
		return getIntStringVectorResponse();
	}

	return NULL;
}

IntVectorResult* APICallPatternClause::getIntVectorResponse() {
	vector<unsigned int> result;
	string synonym = patternClause.synonym;
	string firstParam = patternClause.firstParam;
	string secondParam = patternClause.secondParam;

	if (paramType == make_pair(VARIABLE, UNDERSCORE)) { // a("v", _)
		// Becomes Modifies(a, "v") 
		result = PKB::getAllStmtThatModifiesVariable(ASSIGNMENT_VAR, patternClause.firstParam);
		cout << "PKB::getAllStmtThatModifiesVariable(ASSIGNMENT_VAR, patternClause.firstParam) // a('v', _) " << endl;
	}
	else if (paramType == make_pair(UNDERSCORE, CONSTANT)) { // a(_, _"5"_)
		// Uses(a, "5")
		result = PKB::getAllAssignsWithConstant(secondParam);
		cout << "PKB::getAllAssignsWithConstant(secondParam) // a(_, _'5'_)" << endl;
	}
	else if (paramType == make_pair(UNDERSCORE, VARIABLE)) { // a(_,_"var"_)
		// Uses(a, "var")
		result = PKB::getAllStmtsThatUsesVariable(ASSIGNMENT_VAR, patternClause.secondParam);
		cout << "PKB::getAllStmtsThatUsesVariable(ASSIGNMENT_VAR, patternClause.secondParam)  // a(_,_'var'_)" << endl;
	}
	else if (paramType == make_pair(VARIABLE, CONSTANT)) { // a('v', _'5'_)
		// Modifies(a,"v") - Get all assignments that modifies "v"
		vector<unsigned int> all = PKB::getAllStmtThatModifiesVariable(ASSIGNMENT_VAR, firstParam);

		// Uses(a, "5") - Loop through all assignments and get the assignment that uses constant 5
		for (unsigned int i : all) {
			if (PKB::isAssignmentUsesConstant(i, secondParam)) {
				result.push_back(i);
			}
		}

		cout << "// a('v', _'5'_)" << endl;
	}
	else if (paramType == make_pair(VARIABLE, VARIABLE)) { // a('v', _'h'_)
		// Modifies(a,"v") - Get all assignments that modifies "v"
		vector<unsigned int> all = PKB::getAllStmtThatModifiesVariable(ASSIGNMENT_VAR, firstParam);

		// Uses(a, "h") - Loop through all assignments and get the assignment that uses variable h
		for (unsigned int i : all) {
			if (PKB::isUses(i, secondParam)) {
				result.push_back(i);
			}
		}

		cout << "// a('v', _'h'_)" << endl;
	}
	else if (paramType == make_pair(UNDERSCORE, UNDERSCORE)) {
		cout << "// a(_,_)" << endl;
		cout << "result = PKB::getAssigns();" << endl;
		result = PKB::getAssigns();
	}

	IntVectorResult* intVectorResult = new IntVectorResult(result, synonym);
	return intVectorResult;
}

IntStringPairVectorResult* APICallPatternClause::getIntStringVectorResponse() {
	vector< pair<unsigned int, string> > result;
	string synonym1 = patternClause.synonym;
	string firstParam = patternClause.firstParam;
	string secondParam = patternClause.secondParam;

	if (paramType == make_pair(SYNONYM, UNDERSCORE)) {	// a(v, _)
		// Modifies(a, v)
		result = PKB::getAllStmtModifiesVariablePairs(ASSIGNMENT_VAR);
		cout << "// a(v, _)" << endl;
	}
	else if (paramType == make_pair(SYNONYM, CONSTANT)) { // a(v, _'5'_)
		// Modifies(a, v)
		vector< pair<unsigned int, string> > all = PKB::getAllStmtModifiesVariablePairs(ASSIGNMENT_VAR);
		
		// Uses(a, "5")
		for (pair<unsigned int, string> i : all) {
			if (PKB::isAssignmentUsesConstant(i.first, secondParam)) {
				result.push_back(i);
			}
		}
		cout << "// a(v, _'5'_)" << endl;
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) { // a(v,_'h'_)
		// Modifies(a, v)
		vector< pair<unsigned int, string> > all = PKB::getAllStmtModifiesVariablePairs(ASSIGNMENT_VAR);
		
		// Uses(a, "h")
		for (pair<unsigned int, string> i : all) {
			if (PKB::isUses(i.first, secondParam)) {
				result.push_back(i);
			}
		}
		cout << "// a(v,_'h'_)" << endl;
	}

	IntStringPairVectorResult *intStrResult = new IntStringPairVectorResult(result, make_pair(synonym1, firstParam));
	return intStrResult;
}