#pragma once
#include "QueryObject.h"
#include <vector>

using namespace std;

class QueryEvaluator {
private:
	QueryObject *queryObject;
public:
	QueryEvaluator(QueryObject *queryObject);

	string evaluateQueryObject();
	string evaluateSingleClause();
	string selectImmediateResults();

	string evaluateClause(SUCH_THAT_CLAUSE clause, string typeOfRs);
	string evaluateNonSynonym(string typeOfRs, pair<string, string> paramType, SUCH_THAT_CLAUSE clause);
	string evaluateOneSynonym(string typeOfRs, pair<string, string> paramType, SUCH_THAT_CLAUSE clause);
	string evaluateTwoSynonym(string typeOfRs, pair<string, string> paramType, SUCH_THAT_CLAUSE clause);
	
	// Result methods
	string processTwoSynonymResults(vector< pair<int, int> > result, SUCH_THAT_CLAUSE clause);
	string processTwoSynonymResults(vector< pair<string, string> > result, SUCH_THAT_CLAUSE clause);
	string processTwoSynonymResults(vector< pair<int, string> > result, SUCH_THAT_CLAUSE clause);
	string noResult();
	
	// Helper methods
	bool synonymIsFoundInParam(SUCH_THAT_CLAUSE clause);
	pair<string, string> getParamType(SUCH_THAT_CLAUSE clause);
	string getIntIntPair(string typeOfRs, SUCH_THAT_CLAUSE clause);
	string getStringStringPair(string typeOfRs, SUCH_THAT_CLAUSE clause);
	string getIntStringPair(string typeOfRs, SUCH_THAT_CLAUSE clause);

	// Static extraction methods
	static string stringVectorToString(vector<string> input);
	static string intVectorToString(vector<int> input);
	static string extractFirstParam(vector < pair<int, int> > input);
	static string extractSecondParam(vector < pair<int, int> > input);
	static string extractFirstParam(vector < pair<string, string> > input);
	static string extractSecondParam(vector < pair<string, string> > input);
	static string extractFirstParam(vector < pair<int, string> > input);
	static string extractSecondParam(vector < pair<int, string> > input);
};