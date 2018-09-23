#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryEvaluator.h"
#include "Keywords.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace keywords::query;

namespace UnitTesting
{
	TEST_CLASS(RemoveDuplicatesTest)
	{
	private:
		QueryObject *queryObject = new QueryObject();
		QueryEvaluator *queryEvaluator = new QueryEvaluator(queryObject);

		vector<string> returnedResult;
		vector<string> expectedResult;
	public:
		TEST_METHOD(RemoveDuplicates)
		{
			vector<string> s = { "sum", "summie", "sums", "a", "b", "bb", "cc",
				"h", "i", "j", "h", "k", "l", "k", "z", "r", "s", "o", "sum", "bb" };
			returnedResult = queryEvaluator->removeDuplicates(s);
			expectedResult = {"sum", "summie", "sums", "a", "b", "bb", "cc", "h", 
				"i", "j", "k", "l", "z", "r", "s", "o"};
			sort(returnedResult.begin(), returnedResult.end());
			sort(expectedResult.begin(), expectedResult.end());
			Assert::IsTrue(returnedResult == expectedResult);
		}
	};
}