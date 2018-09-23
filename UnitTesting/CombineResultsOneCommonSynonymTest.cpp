#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryEvaluator.h"
#include "Keywords.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace keywords::query;

namespace UnitTesting
{
	TEST_CLASS(CombineResultsOneCommonSynonymTest)
	{
	private:
		QueryObject *queryObject;
		QueryEvaluator *queryEvaluator;
		vector<string> selectClause;
		Result *firstResult;
		Result *secondResult;
		vector<string> selectedResult;
		vector<string> expectedResult;
	public:
		/** TWO TOTAL SYNONYMS **/
		TEST_METHOD(TwoTotalSynonymsIntAndInt)
		{
			vector<unsigned int> intResult1 = { 1,2,3,4,5,6,8,9,10,12,20,15 };
			firstResult = new IntVectorResult(intResult1, "s");

			vector<unsigned int> intResult2 = { 6,8,9,10,12,20,15,15,50 };
			secondResult = new IntVectorResult(intResult2, "s");

			vector<string> commonKeys = { "s" };
			
			// Select 's'
			selectClause = { "s" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "6","8","9","10","12","20","15" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		/** THREE TOTAL SYNONYMS **/
		TEST_METHOD(ThreeTotalSynonymsIntIntAndInt)
		{
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
			firstResult = new IntIntPairVectorResult(intIntResult, make_pair("a1", "a2"));

			vector<unsigned int> intResult = { 6,8,9,10,12,20,15,50 };
			secondResult = new IntVectorResult(intResult, "a1");

			vector<string> commonKeys = { "a1" };

			// Select 'a1'
			selectClause = { "a1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "10","6","8" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
			
			// Select 'a2'
			selectClause = { "a2" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "6","3","7","10" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		TEST_METHOD(ThreeTotalSynonymsIntStrAndInt)
		{
			vector<pair<unsigned int, string>> intStrResult = {
				make_pair(1, "v"),
				make_pair(2, "c"),
				make_pair(1, "h"),
				make_pair(1, "z"),
				make_pair(3, "r"),
				make_pair(2, "h"),
				make_pair(4, "z"),
				make_pair(5, "h")
			};
			firstResult = new IntStringPairVectorResult(intStrResult, make_pair("a", "v"));

			vector<unsigned int> intResult = { 5,6,8,9,10,12,20,15,50,1 };
			secondResult = new IntVectorResult(intResult, "a");

			vector<string> commonKeys = { "a" };

			// Select 'a'
			selectClause = { "a" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "1","5" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
			
			// Select 'v'
			selectClause = { "v" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "v","h","z" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		TEST_METHOD(ThreeTotalSynonymsIntStrAndStr)
		{
			vector<pair<unsigned int, string>> intStrResult = {
				make_pair(1, "v"),
				make_pair(2, "c"),
				make_pair(1, "h"),
				make_pair(1, "z"),
				make_pair(3, "r"),
				make_pair(2, "h"),
				make_pair(4, "sum"),
				make_pair(5, "h")
			};
			firstResult = new IntStringPairVectorResult(intStrResult, make_pair("a", "v"));

			vector<string> strResult = { "sum", "r", "k", "p", "var", "s", "t", "h" };
			secondResult = new StringVectorResult(strResult, "v");

			vector<string> commonKeys = { "v" };

			// Select 'v'
			selectClause = { "v" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "r", "sum", "h" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'a'
			selectClause = { "a" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "1","3","2","4","5" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		/** FOUR TOTAL SYNONYMS **/
		TEST_METHOD(FourTotalSynonymsIntIntAndIntStr)
		{
			vector<pair<unsigned int, unsigned int>> intIntResult = {
				make_pair(1, 2),
				make_pair(3, 5),
				make_pair(10, 6),
				make_pair(4, 8),
				make_pair(7, 9),
				make_pair(8, 10),
				make_pair(6, 3),
			};
			firstResult = new IntIntPairVectorResult(intIntResult, make_pair("a1", "a2"));

			vector<pair<unsigned int, string>> intStrResult = {
				make_pair(1, "v"),
				make_pair(2, "c"),
				make_pair(1, "h"),
				make_pair(1, "z"),
				make_pair(3, "r"),
				make_pair(6, "p"),
				make_pair(2, "h"),
				make_pair(4, "sum"),
				make_pair(5, "h"),
				make_pair(6, "sum")
			};
			secondResult = new IntStringPairVectorResult(intStrResult, make_pair("a1", "v"));

			vector<string> commonKeys = { "a1" };
			
			// Select 'a1'
			selectClause = { "a1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "1","3","4","6" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'a2'
			selectClause = { "a2" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "2","5","8","3" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'v'
			selectClause = { "v" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "v","h","z","r","sum","p"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		TEST_METHOD(FourTotalSynonymsIntStrAndIntStr)
		{
			vector<pair<unsigned int, string>> intStrResult1 = {
				make_pair(1, "v"),
				make_pair(2, "c"),
				make_pair(1, "h"),
				make_pair(1, "z"),
				make_pair(3, "r"),
				make_pair(6, "p"),
				make_pair(2, "var"),
				make_pair(4, "sum"),
				make_pair(5, "h"),
				make_pair(6, "sum")
			};
			firstResult = new IntStringPairVectorResult(intStrResult1, make_pair("a1", "v"));
			 
			vector<pair<unsigned int, string>> intStrResult2 = {
				make_pair(1, "a"),
				make_pair(2, "b"),
				make_pair(1, "c"),
				make_pair(1, "d"),
				make_pair(3, "e"),
				make_pair(6, "f"),
			};
			secondResult = new IntStringPairVectorResult(intStrResult2, make_pair("a1", "v1"));

			vector<string> commonKeys = { "a1" };

			// Select 'a1'
			selectClause = { "a1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "1","2","3","6" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'v'
			selectClause = { "v" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "v","h","z","c","var","r","p","sum" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'v1'
			selectClause = { "v1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "a","b","c","d","e","f" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			commonKeys = { "v" };
			firstResult = new IntStringPairVectorResult(intStrResult1, make_pair("a1", "v"));
			secondResult = new IntStringPairVectorResult(intStrResult2, make_pair("a", "v"));

			// Select 'v'
			selectClause = { "v" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "c" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'a1'
			selectClause = { "a1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "2" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'a'
			selectClause = { "a" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "1" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		TEST_METHOD(FourTotalSynonymsStrStrAndIntStr)
		{
			vector<pair<string, string>> strStrResult = {
				make_pair("main", "r"),
				make_pair("sum", "p"),
				make_pair("sum", "q"),
				make_pair("main", "s"),
				make_pair("mul", "a"),
				make_pair("method", "var"),
				make_pair("methodOne", "var")
			};
			firstResult = new StringStringPairVectorResult(strStrResult, make_pair("p", "v1"));
			
			vector<pair<unsigned int, string>> intStrResult = {
				make_pair(1, "var"),
				make_pair(2, "b"),
				make_pair(1, "c"),
				make_pair(1, "d"),
				make_pair(3, "e"),
				make_pair(6, "f"),
				make_pair(6, "a"),
				make_pair(9, "s")
			};
			secondResult = new IntStringPairVectorResult(intStrResult, make_pair("a", "v1"));

			vector<string> commonKeys = { "v1" };

			// Select 'v1'
			selectClause = { "v1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "s","a","var" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'p'
			selectClause = { "p" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "main","mul","method","methodOne" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select 'a'
			selectClause = { "a" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->oneCommonSynonym(firstResult, secondResult, commonKeys);
			expectedResult = { "1","6","9" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}
	};
}