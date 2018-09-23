#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryEvaluator.h"
#include "Keywords.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace keywords::query;

namespace UnitTesting
{
	TEST_CLASS(CombineResultsTwoCommonSynonymsTest)
	{
	private:
		vector<string> commonKeys;
		QueryObject *queryObject;
		QueryEvaluator *queryEvaluator;
		Result *firstResult;
		Result *secondResult;
		vector<string> selectedResult;
		vector<string> expectedResult;
	public:
		TEST_METHOD(TwoCommonSynonyms)
		{
			/**
			For both the results to have two common synonyms, both synonyms are the same type
			Pattern clause will never return a StringStringPairVector result hence the only possible two
			common synonyms would be IntStringPair
			**/
			vector<pair<unsigned int, string>> result = {
				make_pair(1, "sum"),
				make_pair(2, "c"),
				make_pair(1, "h"),
				make_pair(1, "z"),
				make_pair(3, "r"),
				make_pair(2, "h"),
				make_pair(4, "z"),
				make_pair(5, "h")
			};
			pair<string, string> synonyms = { make_pair("a", "v") };
			firstResult = new IntStringPairVectorResult(result, synonyms);

			result = {
				make_pair(1, "sum"),
				make_pair(1, "h"),
				make_pair(3, "o"),
				make_pair(3, "h"),
				make_pair(3, "r"),
				make_pair(5, "z"),
				make_pair(2, "h"),
				make_pair(6, "r")
			};
			secondResult = new IntStringPairVectorResult(result, synonyms);

			commonKeys = { "a", "v" };
			queryObject = new QueryObject();

			// Select Synonym is "a"
			vector<string> selectClause = { "a" };
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->twoCommonSynonyms(firstResult, secondResult, commonKeys);
			expectedResult = {"1", "3", "2"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);

			// Select Synonym is "v"
			selectClause = { "v" };
			queryObject->setSelectClause(selectClause);
			queryEvaluator = new QueryEvaluator(queryObject);
			selectedResult = queryEvaluator->twoCommonSynonyms(firstResult, secondResult, commonKeys);
			expectedResult = {"sum", "h", "r"};
			sort(selectedResult.begin(), selectedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(selectedResult == expectedResult);
		}

	};
}