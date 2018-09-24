#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryEvaluator.h"
#include "Keywords.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace keywords::query;

namespace UnitTesting
{
	TEST_CLASS(CombineResultsTest)
	{
	private:
		QueryObject *queryObject;
		QueryEvaluator *queryEvaluator;
		Result *firstResult;
		Result *secondResult;
		vector<string> selectClause;
		vector<string> selectedResult;
		vector<string> expectedResult;


		vector<pair<unsigned int, string>> intStrResult = { 
			make_pair(1, "v"),
			make_pair(2, "c"),
			make_pair(1, "h"),
			make_pair(1, "z"),
			make_pair(3, "r"),
			make_pair(2, "var"),
			make_pair(4, "z"),
			make_pair(5, "h") 
		};
		vector<pair<unsigned int, unsigned int>> intIntResult = { 
			make_pair(1, 2),
			make_pair(3, 5),
			make_pair(10, 6),
			make_pair(4, 8),
			make_pair(7, 9),
			make_pair(8, 10),
			make_pair(6, 3),
			make_pair(6, 7) 
		};
		vector<pair<string, string>> strStrResult = {
			make_pair("main", "r"),
			make_pair("sum", "p"),
			make_pair("sum", "q"),
			make_pair("main", "s"),
			make_pair("mul", "a"),
			make_pair("method", "var"),
			make_pair("methodOne", "var") 
		};
		vector<unsigned int> intResult = { 5,6,8,9,10,12,20,15,50,1 };
		vector<string> strResult = { "sum", "r", "k", "p", "var", "s", "t", "h" };
	public:
		TEST_METHOD(NoCommonSynonymPath)
		{
			queryObject = new QueryObject();

			firstResult = new IntStringPairVectorResult(intStrResult, make_pair("a1","v1"));
			secondResult = new IntStringPairVectorResult(intStrResult, make_pair("a2","v2"));

			// Select 'a1'
			selectClause = { "a1" };
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->combineResults(firstResult, secondResult);
			expectedResult = { "1","2","3","4","5" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
			
			// Select 'v1'
			selectClause = { "v1" };
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->combineResults(firstResult, secondResult);
			expectedResult = { "v","c","h","z","r","var" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'a2'
			selectClause = { "a2" };
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->combineResults(firstResult, secondResult);
			expectedResult = { "1","2","3","4","5" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'v2'
			selectClause = { "v2" };
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->combineResults(firstResult, secondResult);
			expectedResult = { "v","c","h","z","r","var" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		TEST_METHOD(OneCommonSynonymPath)
		{
			queryObject = new QueryObject();

			firstResult = new IntIntPairVectorResult(intIntResult, make_pair("a1", "a2"));
			secondResult = new IntStringPairVectorResult(intStrResult, make_pair("a2", "v"));
			
			// Select 'a2'
			selectClause = { "a2" };
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->combineResults(firstResult, secondResult);
			expectedResult = { "2","5","3" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'a1'
			selectClause = { "a1" };
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->combineResults(firstResult, secondResult);
			expectedResult = { "1","3","6" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'v'
			selectClause = { "v" };
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->combineResults(firstResult, secondResult);
			expectedResult = { "c","h","r","var" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		TEST_METHOD(TwoCommonSynonymPath)
		{
			queryObject = new QueryObject();

			firstResult = new IntStringPairVectorResult(intStrResult, make_pair("a", "v1"));
			secondResult = new IntStringPairVectorResult(intStrResult, make_pair("a", "v1"));
			
			// Select 'a'
			selectClause = { "a" };
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->combineResults(firstResult, secondResult);
			expectedResult = { "1","2","3","4","5" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'v1'
			selectClause = { "v1" };
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->combineResults(firstResult, secondResult);
			expectedResult = { "v","c","h","z","r","var" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

	};
}