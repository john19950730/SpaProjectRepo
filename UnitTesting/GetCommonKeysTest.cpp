#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryEvaluator.h"
#include "Keywords.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace keywords::query;

namespace UnitTesting
{
	TEST_CLASS(GetCommonKeysTest)
	{
	private:
		vector<string> commonKeys;
		QueryObject *queryObject = new QueryObject();
		QueryEvaluator *queryEvaluator = new QueryEvaluator(queryObject);
		Result *firstResult;
		Result *secondResult;
		vector<string> returnedResult;
		vector<string> expectedResult;

		vector<pair<unsigned int, string>> intStrResult = {make_pair(1, "var")};
		vector<pair<unsigned int, unsigned int>> intIntResult = {make_pair(1,2)};
		vector<pair<string, string>> strStrResult = { make_pair("proc", "a") };
		vector<unsigned int> intResult = { 2 };
		vector<string> strResult = { "h" };
	public:
		TEST_METHOD(GetCommonKeyIntStrAndIntInt)
		{
			firstResult = new IntStringPairVectorResult(intStrResult, make_pair("a","v"));
			secondResult = new IntIntPairVectorResult(intIntResult, make_pair("a","a1"));

			returnedResult = queryEvaluator->getCommonKeys(firstResult->getSynonyms(), secondResult->getSynonyms());
			expectedResult = { "a" };
			sort(returnedResult.begin(), returnedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(returnedResult == expectedResult);
		}

		TEST_METHOD(GetCommonKeyIntStrAndStrStr)
		{
			firstResult = new IntStringPairVectorResult(intStrResult, make_pair("a", "v"));
			secondResult = new StringStringPairVectorResult(strStrResult, make_pair("p", "v"));

			returnedResult = queryEvaluator->getCommonKeys(firstResult->getSynonyms(), secondResult->getSynonyms());
			expectedResult = { "v" };
			sort(returnedResult.begin(), returnedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(returnedResult == expectedResult);
		}

		TEST_METHOD(GetCommonKeyIntStrAndInt)
		{
			firstResult = new IntStringPairVectorResult(intStrResult, make_pair("a", "v"));
			secondResult = new IntVectorResult(intResult, "a1");

			returnedResult = queryEvaluator->getCommonKeys(firstResult->getSynonyms(), secondResult->getSynonyms());
			expectedResult = {};
			sort(returnedResult.begin(), returnedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(returnedResult == expectedResult);
		}

		TEST_METHOD(GetCommonKeyIntStrAndStr)
		{
			firstResult = new IntStringPairVectorResult(intStrResult, make_pair("a", "v"));
			secondResult = new StringVectorResult(strResult, "v");

			returnedResult = queryEvaluator->getCommonKeys(firstResult->getSynonyms(), secondResult->getSynonyms());
			expectedResult = {"v"};
			sort(returnedResult.begin(), returnedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(returnedResult == expectedResult);
		}

		TEST_METHOD(GetCommonKeyIntIntAndStrStr)
		{
			firstResult = new IntIntPairVectorResult(intIntResult, make_pair("s1", "s2"));
			secondResult = new StringStringPairVectorResult(strStrResult, make_pair("p", "v"));

			returnedResult = queryEvaluator->getCommonKeys(firstResult->getSynonyms(), secondResult->getSynonyms());
			expectedResult = {};
			sort(returnedResult.begin(), returnedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(returnedResult == expectedResult);
		}

		TEST_METHOD(GetCommonKeyIntIntAndInt)
		{
			firstResult = new IntIntPairVectorResult(intIntResult, make_pair("a1", "a2"));
			secondResult = new IntVectorResult(intResult, "a2");

			returnedResult = queryEvaluator->getCommonKeys(firstResult->getSynonyms(), secondResult->getSynonyms());
			expectedResult = { "a2" };
			sort(returnedResult.begin(), returnedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(returnedResult == expectedResult);
		}

		TEST_METHOD(GetCommonKeyIntIntAndStr)
		{
			firstResult = new IntIntPairVectorResult(intIntResult, make_pair("s", "a"));
			secondResult = new StringVectorResult(strResult, "v");

			returnedResult = queryEvaluator->getCommonKeys(firstResult->getSynonyms(), secondResult->getSynonyms());
			expectedResult = {};
			sort(returnedResult.begin(), returnedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(returnedResult == expectedResult);
		}

		TEST_METHOD(GetCommonKeyStrStrAndInt)
		{
			firstResult = new StringStringPairVectorResult(strStrResult, make_pair("p", "v"));
			secondResult = new IntVectorResult(intResult, "a1");

			returnedResult = queryEvaluator->getCommonKeys(firstResult->getSynonyms(), secondResult->getSynonyms());
			expectedResult = {};
			sort(returnedResult.begin(), returnedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(returnedResult == expectedResult);
		}

		TEST_METHOD(GetCommonKeyStrStrAndStr)
		{
			firstResult = new StringStringPairVectorResult(strStrResult, make_pair("p1", "v"));
			secondResult = new StringVectorResult(strResult, "p1");

			returnedResult = queryEvaluator->getCommonKeys(firstResult->getSynonyms(), secondResult->getSynonyms());
			expectedResult = {"p1"};
			sort(returnedResult.begin(), returnedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(returnedResult == expectedResult);
		}

		TEST_METHOD(GetCommonKeyIntAndStr)
		{
			firstResult = new IntVectorResult(intResult, "a1");
			secondResult = new StringVectorResult(strResult, "v1");

			returnedResult = queryEvaluator->getCommonKeys(firstResult->getSynonyms(), secondResult->getSynonyms());
			expectedResult = {};
			sort(returnedResult.begin(), returnedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(returnedResult == expectedResult);
		}
	};
}