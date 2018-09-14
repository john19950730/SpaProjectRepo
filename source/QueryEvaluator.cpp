#include "QueryEvaluator.h"
#include "Keywords.h"
#include "Utility.h"
#include "PKB.h"

#include <iostream>

using namespace std;
using namespace keywords::query;
using namespace keywords::clauseParamType;

QueryEvaluator::QueryEvaluator(QueryObject *queryObject) {
	this->queryObject = queryObject;
}

string QueryEvaluator::evaluateQueryObject() {	
	if (!queryObject->hasClauses()) return selectImmediateResults();

	// First milestone - evaluate only one clause
	if (queryObject->getNumberOfClauses() == 1) return evaluateSingleClause();
	
	return "Error";
}

// Return results immediately if there are no clauses
string QueryEvaluator::selectImmediateResults() {
	string selectSynonym = queryObject->getSelectClause().at(0);	// Only one select synonym for iteration 1
	string synonymType = queryObject->getSynonymTable()[selectSynonym];

	if (synonymType == ASSIGNMENT_VAR) return "allAssignmentStmts";
	else if (synonymType == VARIABLE_VAR) return "allVariableStmts";
	else if (synonymType == STMT_VAR) return "allStmts";
	else if (synonymType == PROC_VAR) return "allProcedures";
	else if (synonymType == IF_VAR) return "allIfStmts";
	else if (synonymType == WHILE_VAR) return "allWhileStmts";
	else if (synonymType == READ_VAR) return "allReadStmts";
	else if (synonymType == PRINT_VAR) return "allPrintStmts";

	return "";
}

string QueryEvaluator::evaluateSingleClause() {
	if (queryObject->hasUsesClause()) return evaluateClause(queryObject->getUsesClause().at(0), USES_RS);
	else if (queryObject->hasModifiesClause()) return evaluateClause(queryObject->getModifiesClause().at(0), MODIFIES_RS);
	else if (queryObject->hasParentClause()) return evaluateClause(queryObject->getParentClause().at(0), PARENT_RS);
	else if (queryObject->hasFollowsClause()) return evaluateClause(queryObject->getFollowsClause().at(0), FOLLOWS_RS);
}

string QueryEvaluator::evaluateClause(SUCH_THAT_CLAUSE clause, string typeOfRs) {
	// Extract the clause information
	map<string, string> synonymTable = queryObject->getSynonymTable();
	string firstParam = clause.firstParameter;
	string secondParam = clause.secondParameter;
	pair<string, string> paramType = getParamType(clause);

	if (paramType == make_pair(STMT_NO, VARIABLE) || paramType == make_pair(PROC_NAME, VARIABLE)
		|| paramType == make_pair(STMT_NO, STMT_NO)) {
		return evaluateNonSynonym(typeOfRs, paramType, clause);
	}
	else if (paramType == make_pair(PROC_NAME, SYNONYM) || paramType == make_pair(PROC_NAME, UNDERSCORE)
		|| paramType == make_pair(SYNONYM, VARIABLE) || paramType == make_pair(STMT_NO, SYNONYM)
		|| paramType == make_pair(STMT_NO, UNDERSCORE)) {
		return evaluateOneSynonym(typeOfRs, paramType, clause);
	}
	else if (paramType == make_pair(SYNONYM, SYNONYM) || paramType == make_pair(SYNONYM, UNDERSCORE) || 
		paramType == make_pair(UNDERSCORE, SYNONYM)) {
		return evaluateTwoSynonym(typeOfRs, paramType, clause);
	}
}

string QueryEvaluator::evaluateNonSynonym(string typeOfRs, pair<string, string> paramType, SUCH_THAT_CLAUSE clause) {
	bool isRsValid = false;
	
	if (typeOfRs == USES_RS) { 
		if (paramType == make_pair(STMT_NO, VARIABLE)) {
			isRsValid = PKB::isUses(stoi(clause.firstParameter), clause.secondParameter);
		}
		else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
			cout << "Proc uses name" << endl;
			return "";
		}
	}
	else if (typeOfRs == MODIFIES_RS) {
		if (paramType == make_pair(STMT_NO, VARIABLE)) {
			isRsValid = PKB::isModifies(stoi(clause.firstParameter), clause.secondParameter);
		}
		else if (paramType == make_pair(PROC_NAME, VARIABLE)) {
			cout << "Proc modifies name" << endl;
			return "";
		}
	}
	else if (typeOfRs == FOLLOWS_RS) {
		if (paramType == make_pair(STMT_NO, STMT_NO)) {
			isRsValid = PKB::isFollows(stoi(clause.firstParameter), stoi(clause.secondParameter), clause.hasTransitiveClosure);
		}
	}
	else if (typeOfRs == PARENT_RS) {
		if (paramType == make_pair(STMT_NO, STMT_NO)) {
			isRsValid = PKB::isParent(stoi(clause.firstParameter), stoi(clause.secondParameter), clause.hasTransitiveClosure);
		}
	}
	
	string result = isRsValid ? selectImmediateResults() : noResult() ;
	return result;
}

string QueryEvaluator::evaluateOneSynonym(string typeOfRs, pair<string, string> paramType, SUCH_THAT_CLAUSE clause) {
	map<string, string> synonymTable = queryObject->getSynonymTable();
	
	vector<string> stringResult;
	bool stringResultIsset = false;
	vector<int> intResult;
	bool intResultIsset = false;

	string firstParam = clause.firstParameter;
	string secondParam = clause.secondParameter;

	if (paramType == make_pair(STMT_NO, SYNONYM) || paramType == make_pair(STMT_NO, UNDERSCORE)) {
		if (typeOfRs == USES_RS) {
			stringResult = PKB::getAllVariablesUsedByStmtNo(stoi(firstParam));
			stringResultIsset = true;
		}
		else if (typeOfRs == MODIFIES_RS) {
			stringResult = PKB::getAllVariablesModifiedByStmtNo(stoi(firstParam));
			stringResultIsset = true;
		}
		else if (typeOfRs == FOLLOWS_RS) {
			intResult = PKB::getStmtNoThatFollows(stoi(firstParam), clause.hasTransitiveClosure);
			intResultIsset = true;
		}
		else if (typeOfRs == PARENT_RS) {
			intResult = PKB::getStmtNoThatIsChildOf(stoi(firstParam), clause.hasTransitiveClosure);
			intResultIsset = true;
		}
	}
	else if (paramType == make_pair(PROC_NAME, SYNONYM) || paramType == make_pair(PROC_NAME, UNDERSCORE)) {
		if (typeOfRs == USES_RS) {
			stringResult = PKB::getAllVariablesUsedByProcedures(firstParam);
			stringResultIsset = true;
		}
		else if (typeOfRs == MODIFIES_RS) {
			stringResult = PKB::getAllVariablesModifiedByProcedures(firstParam);
			stringResultIsset = true;
		}
	}
	// Check here onwards
	else if (paramType == make_pair(SYNONYM, STMT_NO) || paramType == make_pair(SYNONYM, UNDERSCORE)) {
		if (typeOfRs == FOLLOWS_RS) {
			intResult = PKB::getStmtNoThatIsFollowedBy(stoi(secondParam), clause.hasTransitiveClosure);
			intResultIsset = true;
		}
		else if (typeOfRs == PARENT_RS) {
			intResult = PKB::getStmtNoThatIsParentOf(stoi(secondParam), clause.hasTransitiveClosure);
			intResultIsset = true;
		}
	}
	else if (paramType == make_pair(SYNONYM, VARIABLE)) {
		if (synonymTable[firstParam] == ASSIGNMENT_VAR) {
			if (typeOfRs == USES_RS) {
				intResult = PKB::getAllAssignmentThatUses(secondParam);
				intResultIsset = true;
			}
			else if (typeOfRs == MODIFIES_RS) {
				intResult = PKB::getAllAssignmentThatModifies(secondParam);
				intResultIsset = true;
			}
		}
		else if (synonymTable[firstParam] == STMT_VAR) {
			if (typeOfRs == USES_RS) {
				intResult = PKB::getAllStmtThatUses(secondParam);
				intResultIsset = true;
			}
			else if (typeOfRs == MODIFIES_RS) {
				intResult = PKB::getAllStmtThatModifies(secondParam);
				intResultIsset = true;
			}
		}
		else if (synonymTable[firstParam] == PROC_VAR) {
			if (typeOfRs == USES_RS) {
				stringResult = PKB::getAllProcedureThatUses(secondParam);
				stringResultIsset = true;
			}
			else if (typeOfRs == MODIFIES_RS) {
				stringResult = PKB::getAllProcedureThatModifies(secondParam);
				stringResultIsset = true;
			}
		}
		else if (synonymTable[firstParam] == IF_VAR) {
			if (typeOfRs == USES_RS) {
				intResult = PKB::getAllIfThatUses(secondParam);
				intResultIsset = true;
			}
			else if (typeOfRs == MODIFIES_RS) {
				intResult = PKB::getAllIfThatModifies(secondParam);
				intResultIsset = true;
			}
		}
		else if (synonymTable[firstParam] == WHILE_VAR) {
			if (typeOfRs == USES_RS) {
				intResult = PKB::getAllWhileThatUses(secondParam);
				intResultIsset = true;
			}
			else if (typeOfRs == MODIFIES_RS) {
				intResult = PKB::getAllWhileThatModifies(secondParam);
				intResultIsset = true;
			}
		}
		else if (synonymTable[firstParam] == READ_VAR) {
			if (typeOfRs == MODIFIES_RS) {
				intResult = PKB::getAllReadThatModifies(secondParam);
				intResultIsset = true;
			}
		}
		else if (synonymTable[firstParam] == PRINT_VAR) {
			if (typeOfRs == USES_RS) {
				intResult = PKB::getAllPrintThatUses(secondParam);
				intResultIsset = true;
			}
		}
	}

	if (stringResultIsset) {
		if (stringResult.size() > 0) {
			if(synonymIsFoundInParam(clause)) return stringVectorToString(stringResult);
			else return selectImmediateResults();
		}
		else return noResult();
	}
	else {
		if (intResult.size() > 0) {
			if (synonymIsFoundInParam(clause)) return intVectorToString(intResult);
			else return selectImmediateResults();
		}
		else return noResult();
	}

}

string QueryEvaluator::evaluateTwoSynonym(string typeOfRs, pair<string, string> paramType, SUCH_THAT_CLAUSE clause) {
	vector< pair<int, int> > result;

	if (typeOfRs == FOLLOWS_RS) {
		result = PKB::getAllFollowsPair(clause.hasTransitiveClosure);
	}
	else if (typeOfRs == PARENT_RS) {
		result = PKB::getAllParentPair(clause.hasTransitiveClosure);
	}

	return processTwoSynonymResults(result, clause);
}

pair<string, string> QueryEvaluator::getParamType(SUCH_THAT_CLAUSE clause) {
	pair<string, string> paramType(SYNONYM, SYNONYM);

	if (!clause.firstParamIsSynonym) {
		Utility::isInteger(clause.firstParameter) ? paramType.first = STMT_NO : paramType.first = PROC_NAME;
	}
	
	if (!clause.secondParamIsSynonym) {
		Utility::isInteger(clause.secondParameter) ? paramType.second = STMT_NO : paramType.second = VARIABLE;
	}

	if (Utility::isUnderscore(clause.firstParameter)) paramType.first = UNDERSCORE;
	if (Utility::isUnderscore(clause.secondParameter)) paramType.second = UNDERSCORE;

	return paramType;
}

string QueryEvaluator::processTwoSynonymResults(vector< pair<int, int> > result, SUCH_THAT_CLAUSE clause) {
	string selectSynonym = queryObject->getSelectClause().at(0);
	if (!synonymIsFoundInParam(clause)) return selectImmediateResults();

	string extractedResult = selectSynonym == clause.firstParameter ? extractFirstParam(result) : extractSecondParam(result);
	return extractedResult;
}

string QueryEvaluator::noResult() {
	return "";
}

string QueryEvaluator::stringVectorToString(vector<string> input) {
	string s = "";
	for (string i : input) {
		s += " " + i;
	}

	return s;
}

string QueryEvaluator::intVectorToString(vector<int> input) {
	string s = "";
	for (int i : input) {
		s += " " + to_string(i);
	}

	return s;
}

string QueryEvaluator::extractFirstParam(vector < pair<int, int> > input) {
	string s = "";
	for (pair<int, int> i : input) {
		s += " " + to_string(i.first);
	}

	return s;
}

string QueryEvaluator::extractSecondParam(vector < pair<int, int> > input) {
	string s = "";
	for (pair<int, int> i : input) {
		s += " " + to_string(i.second);
	}

	return s;
}

bool QueryEvaluator::synonymIsFoundInParam(SUCH_THAT_CLAUSE clause) {
	string selectSynonym = queryObject->getSelectClause().at(0);
	return (selectSynonym == clause.firstParameter || selectSynonym == clause.secondParameter);
}