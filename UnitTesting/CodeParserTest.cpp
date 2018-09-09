#include "CppUnitTest.h"
#include "CodeParser.h"
#include "stdafx.h"
#include "CodeParser.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(CodeParserTest)
	{
	public:

		TEST_METHOD(ParseTest)
		{
			int parseVal;
			parseVal = CodeParser::parse("TestingString");
			Assert::AreEqual(0, parseVal);
			// TODO: Your test code here
		}

	};
}