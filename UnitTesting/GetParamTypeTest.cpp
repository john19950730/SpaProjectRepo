#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryEvaluator.h"
#include "Keywords.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace keywords::query;
using namespace keywords::clauseParamType;

namespace UnitTesting
{
	TEST_CLASS(GetParamTypeTest)
	{
	private:
		QueryObject *queryObject = new QueryObject();
		QueryEvaluator *queryEvaluator = new QueryEvaluator(queryObject);
		SUCH_THAT_CLAUSE suchThatClause;
		PATTERN_CLAUSE patternClause;

		pair<string, string> returnedParamType;
		pair<string, string> expectedParamType;
	public:
		TEST_METHOD(GetParamTypeOfSuchThatClauseStmtVar)
		{
			// (1,"v")
			suchThatClause.firstParameter = "1";
			suchThatClause.firstParamIsSynonym = false;
			suchThatClause.secondParameter = "v";
			suchThatClause.secondParamIsSynonym = false;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(STMT_NO, VARIABLE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseStmtSyn)
		{
			// (1,v)
			suchThatClause.firstParameter = "1";
			suchThatClause.firstParamIsSynonym = false;
			suchThatClause.secondParameter = "v";
			suchThatClause.secondParamIsSynonym = true;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(STMT_NO, SYNONYM);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseStmtUnderscore)
		{
			// (1,_)
			suchThatClause.firstParameter = "1";
			suchThatClause.firstParamIsSynonym = false;
			suchThatClause.secondParameter = "_";
			suchThatClause.secondParamIsSynonym = false;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(STMT_NO, UNDERSCORE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseProcVar)
		{
			// ("procName","v")
			suchThatClause.firstParameter = "procName";
			suchThatClause.firstParamIsSynonym = false;
			suchThatClause.secondParameter = "v";
			suchThatClause.secondParamIsSynonym = false;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(PROC_NAME, VARIABLE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseProcSyn)
		{
			// ("procName",v)
			suchThatClause.firstParameter = "procName";
			suchThatClause.firstParamIsSynonym = false;
			suchThatClause.secondParameter = "v";
			suchThatClause.secondParamIsSynonym = true;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(PROC_NAME, SYNONYM);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseProcUnderscore)
		{
			// ("procName",_)
			suchThatClause.firstParameter = "procName";
			suchThatClause.firstParamIsSynonym = false;
			suchThatClause.secondParameter = "_";
			suchThatClause.secondParamIsSynonym = false;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(PROC_NAME, UNDERSCORE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseSynVar)
		{
			// (p,"v")
			suchThatClause.firstParameter = "p";
			suchThatClause.firstParamIsSynonym = true;
			suchThatClause.secondParameter = "v";
			suchThatClause.secondParamIsSynonym = false;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(SYNONYM, VARIABLE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseSynSyn)
		{
			// (a,v)
			suchThatClause.firstParameter = "a";
			suchThatClause.firstParamIsSynonym = true;
			suchThatClause.secondParameter = "v";
			suchThatClause.secondParamIsSynonym = true;
			suchThatClause.hasTransitiveClosure = false;
			
			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(SYNONYM, SYNONYM);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseSynUnderscore)
		{
			// (a,_)
			suchThatClause.firstParameter = "a";
			suchThatClause.firstParamIsSynonym = true;
			suchThatClause.secondParameter = "_";
			suchThatClause.secondParamIsSynonym = false;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(SYNONYM, UNDERSCORE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseStmtStmt)
		{
			// (1,2)
			suchThatClause.firstParameter = "1";
			suchThatClause.firstParamIsSynonym = false;
			suchThatClause.secondParameter = "2";
			suchThatClause.secondParamIsSynonym = false;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(STMT_NO, STMT_NO);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseSynStmt)
		{
			// (s,2)
			suchThatClause.firstParameter = "s";
			suchThatClause.firstParamIsSynonym = true;
			suchThatClause.secondParameter = "2";
			suchThatClause.secondParamIsSynonym = false;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(SYNONYM, STMT_NO);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseUnderscoreStmt)
		{
			// (_,2)
			suchThatClause.firstParameter = "_";
			suchThatClause.firstParamIsSynonym = false;
			suchThatClause.secondParameter = "2";
			suchThatClause.secondParamIsSynonym = false;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(UNDERSCORE, STMT_NO);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseUnderscoreSyn)
		{
			// (_,a)
			suchThatClause.firstParameter = "_";
			suchThatClause.firstParamIsSynonym = false;
			suchThatClause.secondParameter = "a";
			suchThatClause.secondParamIsSynonym = true;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(UNDERSCORE, SYNONYM);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfSuchThatClauseUnderscoreUnderscore)
		{
			// (_,_)
			suchThatClause.firstParameter = "_";
			suchThatClause.firstParamIsSynonym = false;
			suchThatClause.secondParameter = "_";
			suchThatClause.secondParamIsSynonym = false;
			suchThatClause.hasTransitiveClosure = false;

			returnedParamType = queryEvaluator->getParamType(suchThatClause);
			expectedParamType = make_pair(UNDERSCORE, UNDERSCORE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}
		
		TEST_METHOD(GetParamTypeOfPatternClauseSynUnderscore)
		{
			// a(v,_)
			patternClause.firstParam = "v";
			patternClause.firstParamIsSynonym = true;
			patternClause.secondParam = "_";

			returnedParamType = queryEvaluator->getParamType(patternClause);
			expectedParamType = make_pair(SYNONYM, UNDERSCORE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfPatternClauseSynConstant)
		{
			// a(v,_"5"_)
			patternClause.firstParam = "v";
			patternClause.firstParamIsSynonym = true;
			patternClause.secondParam = "5";

			returnedParamType = queryEvaluator->getParamType(patternClause);
			expectedParamType = make_pair(SYNONYM, CONSTANT);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfPatternClauseSynVar)
		{
			// a(v,_"h"_)
			patternClause.firstParam = "v";
			patternClause.firstParamIsSynonym = true;
			patternClause.secondParam = "h";

			returnedParamType = queryEvaluator->getParamType(patternClause);
			expectedParamType = make_pair(SYNONYM, VARIABLE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfPatternClauseUnderscoreUnderscore)
		{
			// a(_,_)
			patternClause.firstParam = "_";
			patternClause.firstParamIsSynonym = false;
			patternClause.secondParam = "_";

			returnedParamType = queryEvaluator->getParamType(patternClause);
			expectedParamType = make_pair(UNDERSCORE, UNDERSCORE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfPatternClauseUnderscoreConstant)
		{
			// a(_,_"5"_)
			patternClause.firstParam = "_";
			patternClause.firstParamIsSynonym = false;
			patternClause.secondParam = "5";

			returnedParamType = queryEvaluator->getParamType(patternClause);
			expectedParamType = make_pair(UNDERSCORE, CONSTANT);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfPatternClauseUnderscoreVar)
		{
			// a(_,_"h"_)
			patternClause.firstParam = "_";
			patternClause.firstParamIsSynonym = false;
			patternClause.secondParam = "h";

			returnedParamType = queryEvaluator->getParamType(patternClause);
			expectedParamType = make_pair(UNDERSCORE, VARIABLE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfPatternClauseVarUnderscore)
		{
			// a("v",_)
			patternClause.firstParam = "v";
			patternClause.firstParamIsSynonym = false;
			patternClause.secondParam = "_";

			returnedParamType = queryEvaluator->getParamType(patternClause);
			expectedParamType = make_pair(VARIABLE, UNDERSCORE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfPatternClauseVarConstant)
		{
			// a("v",_"5"_)
			patternClause.firstParam = "v";
			patternClause.firstParamIsSynonym = false;
			patternClause.secondParam = "5";

			returnedParamType = queryEvaluator->getParamType(patternClause);
			expectedParamType = make_pair(VARIABLE, CONSTANT);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}

		TEST_METHOD(GetParamTypeOfPatternClauseVarVar)
		{
			// a("v",_"h"_)
			patternClause.firstParam = "v";
			patternClause.firstParamIsSynonym = false;
			patternClause.secondParam = "h";

			returnedParamType = queryEvaluator->getParamType(patternClause);
			expectedParamType = make_pair(VARIABLE, VARIABLE);
			Assert::IsTrue(returnedParamType == expectedParamType);
		}
	};
}