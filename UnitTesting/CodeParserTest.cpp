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

		//TEST_METHOD(ParseTest)
		//{
		//	int parseVal;
		//	parseVal = CodeParser::parse("TestingString");
		//	Assert::AreEqual(0, parseVal);
		//}

		//TEST_METHOD(ProcessLineTest) 
		//{
		//	int processLineVal;
		//	processLineVal = CodeParser::processLine("Test1", 1);
		//	Assert::AreEqual(0, processLineVal);
		//}

		TEST_METHOD(CheckModifiesTest) 
		{
			string checkModifiesOutput;

			// Testing for assignment of Count
			checkModifiesOutput = CodeParser::checkModifies("assignment", "count = count + 1");
			string intendedOutput = "count";
			Assert::AreEqual(intendedOutput, checkModifiesOutput);

			//Testing for wrong input of Count
			checkModifiesOutput = CodeParser::checkModifies("assignment", "acount = count + 1");
			intendedOutput = "count";
			Assert::AreNotEqual(intendedOutput, checkModifiesOutput);

			// Testing for Read
			checkModifiesOutput = CodeParser::checkModifies("read", "a");
			intendedOutput = "a";
			Assert::AreEqual(intendedOutput, checkModifiesOutput);

			// Testing for 
			checkModifiesOutput = CodeParser::checkModifies("read", "aa");
			intendedOutput = "a";
			Assert::AreNotEqual(intendedOutput, checkModifiesOutput);
		}

	};
}