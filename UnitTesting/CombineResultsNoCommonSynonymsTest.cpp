#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryEvaluator.h"
#include "Keywords.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace keywords::query;

namespace UnitTesting
{

	TEST_CLASS(CombineResultsNoCommonSynonymTest)
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
		// Both results return a pair vector with Pattern clause definitely returning a IntStringVectorResult
		// Pair Case 1: IntString and IntString
		TEST_METHOD(IntStringAndIntString) {
			vector<pair<unsigned int, string>> intStrResult1 = {
				make_pair(1, "v"),
				make_pair(2, "c"),
				make_pair(1, "h"),
				make_pair(1, "z"),
				make_pair(3, "r"),
				make_pair(2, "h"),
				make_pair(4, "z"),
				make_pair(5, "h")
			};
			firstResult = new IntStringPairVectorResult(intStrResult1, make_pair("a", "v"));

			vector<pair<unsigned int, string>> intStrResult2 = {
				make_pair(1, "v"),
				make_pair(3, "h"),
				make_pair(10, "r"),
				make_pair(4, "p"),
				make_pair(7, "z"),
				make_pair(8, "sum")
			};
			secondResult = new IntStringPairVectorResult(intStrResult2, make_pair("a1", "v1"));

			// Select "a"
			selectClause = { "a" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = {"1","2","3","4","5"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "a1"
			selectClause = { "a1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = {"1","3","10","4","7","8"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "v"
			selectClause = { "v" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = {"v","c","h","z","r"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			selectClause = { "v1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = {"v","h","r","p","z","sum"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		// Both results return a pair vector with Pattern clause definitely returning a IntStringVectorResult
		// Pair Case 2: IntString and IntInt
		TEST_METHOD(IntStringAndIntInt) {
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

			vector<pair<unsigned int, unsigned int>> intIntResult = {
				make_pair(1, 2),
				make_pair(3, 5),
				make_pair(10, 6),
				make_pair(4, 8),
				make_pair(7, 9),
				make_pair(8, 10)
			};
			secondResult = new IntIntPairVectorResult(intIntResult, make_pair("a1", "a2"));

			// Select "a"
			selectClause = { "a" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "1","2","3","4","5" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "v"
			selectClause = { "v" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "v","c","h","z","r" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
			
			// Select "a1"
			selectClause = { "a1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = {"1","3","10","4","7","8"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "a2"
			selectClause = { "a2" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = {"2","5","6","8","9","10"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		// Both results return a pair vector with Pattern clause definitely returning a IntStringVectorResult
		// Pair Case 3: IntString and StringString
		TEST_METHOD(IntStringAndStringString) {
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

			vector<pair<string, string>> strStrResult = {
				make_pair("main", "r"),
				make_pair("sum", "p"),
				make_pair("sum", "q"),
				make_pair("main", "s"),
				make_pair("mul", "a"),
				make_pair("method", "var")
			};
			secondResult = new StringStringPairVectorResult(strStrResult, make_pair("p", "v1"));

			// Select "a"
			selectClause = { "a" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "1","2","3","4","5" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "v"
			selectClause = { "v" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "v","c","h","z","r" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
			
			// Select "p"
			selectClause = { "p" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = {"main", "sum", "mul", "method"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "v1"
			selectClause = { "v1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = {"r","p","q","s","a","var"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		// Both results return a singular vector - Pattern will not return a string vector
		// Singular Case 1: Both Int Vector
		TEST_METHOD(IntAndInt) {
			vector<unsigned int> intResult1 = { 1,5,8,10,12,18,11,2,3,6,7 };
			firstResult = new IntVectorResult(intResult1, "a");

			vector<unsigned int> intResult2 = { 1,5,8,6,7,20,23,4,10 };
			secondResult = new IntVectorResult(intResult2, "a1");

			// Select "a"
			selectClause = { "a" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "1","5","8","10","12","18","11","2","3","6","7" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "a1"
			selectClause = { "a1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "1","5","8","6","7","20","23","4","10" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		// Both results return a singular vector - Pattern will not return a string vector
		// Singular Case 2: One Int and One String Vector
		TEST_METHOD(IntAndString) {
			vector<unsigned int> intResult = { 1,5,8,10,12,18,11,2,3,6,7 };
			firstResult = new IntVectorResult(intResult, "a");

			vector<string> strResult = { "h", "r", "k", "p", "q", "s", "t" };
			secondResult = new StringVectorResult(strResult, "v");

			// Select "a"
			selectClause = { "a" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "1","5","8","10","12","18","11","2","3","6","7" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "v"
			selectClause = { "v" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "h", "r", "k", "p", "q", "s", "t" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		// One result return a pair vector, Another result return a singular vector
		// Pair + Singular Case 1: IntString and String
		TEST_METHOD(IntStringAndString) {
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

			vector<string> strResult = { "h", "r", "k", "p", "q", "s", "t" };
			secondResult = new StringVectorResult(strResult, "v1");

			// Select "a"
			selectClause = { "a" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "1","2","3","4","5" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "v"
			selectClause = { "v" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "v","c","h","z","r" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "v1"
			selectClause = { "v1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "h", "r", "k", "p", "q", "s", "t" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		// One result return a pair vector, Another result return a singular vector
		// Pair + Singular Case 2: IntString and Int
		TEST_METHOD(IntStringAndInt) {
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

			vector<unsigned int> intResult = { 1,5,8,10,12,18,11,2,3,6,7 };
			secondResult = new IntVectorResult(intResult, "a1");

			// Select "a"
			selectClause = { "a" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "1","2","3","4","5" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "v"
			selectClause = { "v" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "v","c","h","z","r" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "a1"
			selectClause = { "a1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "1","5","8","10","12","18","11","2","3","6","7" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		// One result return a pair vector, Another result return a singular vector
		// Pair + Singular Case 3: IntInt and String
		TEST_METHOD(IntIntAndString) {
			vector<pair<unsigned int, unsigned int>> intIntResult = {
				make_pair(1, 2),
				make_pair(3, 5),
				make_pair(10, 6),
				make_pair(4, 8),
				make_pair(7, 9),
				make_pair(8, 10)
			};
			firstResult = new IntIntPairVectorResult(intIntResult, make_pair("a1", "a2"));

			vector<string> strResult = { "h", "r", "k", "p", "q", "s", "t" };
			secondResult = new StringVectorResult(strResult, "v1");

			// Select "a1"
			selectClause = { "a1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = {"1","3","10","4","7","8"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "a2"
			selectClause = { "a2" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = {"2","5","6","8","9","10"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "v1"
			selectClause = { "v1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "h", "r", "k", "p", "q", "s", "t" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		// One result return a pair vector, Another result return a singular vector
		// Pair + Singular Case 4: IntInt and Int
		TEST_METHOD(IntIntAndInt) {
			vector<pair<unsigned int, unsigned int>> intIntResult = {
				make_pair(1, 2),
				make_pair(3, 5),
				make_pair(10, 6),
				make_pair(4, 8),
				make_pair(7, 9),
				make_pair(8, 10)
			};
			firstResult = new IntIntPairVectorResult(intIntResult, make_pair("a1", "a2"));

			vector<unsigned int> intResult = { 1,5,8,10,12,18,11,2,3,6,7 };
			secondResult = new IntVectorResult(intResult, "s");

			// Select "a1"
			selectClause = { "a1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "1","3","10","4","7","8" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "a2"
			selectClause = { "a2" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "2","5","6","8","9","10" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "s"
			selectClause = { "s" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "1","5","8","10","12","18","11","2","3","6","7" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

		// One result return a pair vector, Another result return a singular vector
		// Pair + Singular Case 5: StringString and Int
		TEST_METHOD(StringStringAndInt) {
			vector<pair<string, string>> strStrResult = {
				make_pair("main", "r"),
				make_pair("sum", "p"),
				make_pair("sum", "q"),
				make_pair("main", "s"),
				make_pair("mul", "a"),
				make_pair("method", "var")
			};
			firstResult = new StringStringPairVectorResult(strStrResult, make_pair("p", "v1"));

			vector<unsigned int> intResult = { 1,5,8,10,12,18,11,2,3,6,7 };
			secondResult = new IntVectorResult(intResult, "s");

			// Select "p"
			selectClause = { "p" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "main", "sum", "mul", "method" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "v1"
			selectClause = { "v1" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "r", "p", "q", "s", "a", "var" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select "s"
			selectClause = { "s" };
			queryObject = new QueryObject();
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->noCommonSynonym(firstResult, secondResult);
			expectedResult = { "1","5","8","10","12","18","11","2","3","6","7" };
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

	};
}