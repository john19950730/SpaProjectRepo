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
			checkModifiesOutput = CodeParser::checkModifies("read", "read a;");
			intendedOutput = "a";
			Assert::AreEqual(intendedOutput, checkModifiesOutput);

			// Testing for wrong input of Read
			checkModifiesOutput = CodeParser::checkModifies("read", "read aa;");
			intendedOutput = "a";
			Assert::AreNotEqual(intendedOutput, checkModifiesOutput);
		}

		TEST_METHOD(Is_NumberTest) 
		{
			bool checkIs_Number;

			// Test if it returns True when input is Number
			checkIs_Number = CodeParser::is_number("1900");
			Assert::IsTrue(checkIs_Number);

			// Test if it returns False when input contains only Characters
			checkIs_Number = CodeParser::is_number("Hello");
			Assert::IsFalse(checkIs_Number);

			// Test if it returns False when input contains mixture of Numbers and Characters
			checkIs_Number = CodeParser::is_number("1H900");
			Assert::IsFalse(checkIs_Number);

			// Test if it returns False when input contains mixture of Numbers and Characters
			checkIs_Number = CodeParser::is_number("H1900");
			Assert::IsFalse(checkIs_Number);

			// Test if it returns False when input contains mixture of Numbers and Characters
			checkIs_Number = CodeParser::is_number("1900H");
			Assert::IsFalse(checkIs_Number);
		}

		TEST_METHOD(Is_DuplicateTest) 
		{
			bool checkIs_Duplicate;
			std::vector<std::string> sampleVector;
			// loading the vector with data
			sampleVector.push_back("a");
			sampleVector.push_back("apple");

			// Test if it returns True if an Item is found in the vector
			checkIs_Duplicate = CodeParser::is_duplicate("a",sampleVector);
			Assert::IsTrue(checkIs_Duplicate);
			checkIs_Duplicate = CodeParser::is_duplicate("apple", sampleVector);
			Assert::IsTrue(checkIs_Duplicate);

			// Test if it returns False if an Item cannot be found in the vector
			checkIs_Duplicate = CodeParser::is_duplicate("b", sampleVector);
			Assert::IsFalse(checkIs_Duplicate);
			checkIs_Duplicate = CodeParser::is_duplicate("ap", sampleVector);
			Assert::IsFalse(checkIs_Duplicate);
		}

		TEST_METHOD(Is_AppearTest) 
		{
			bool checkIs_Appear;

			// Test if it returns True if a character is contain within a single character String
			checkIs_Appear = CodeParser::is_appeared('a', "a");
			Assert::IsTrue(checkIs_Appear);

			// Test if it returns True if a character is contain within a long String with 'a' at the start
			checkIs_Appear = CodeParser::is_appeared('a', "apple");
			Assert::IsTrue(checkIs_Appear);

			// Test if it returns True if a character is contain within a long String with 'a' within the string
			checkIs_Appear = CodeParser::is_appeared('a', "balloon");
			Assert::IsTrue(checkIs_Appear);

			// Test if it returns False if a character is does not contain within a single character String
			checkIs_Appear = CodeParser::is_appeared('a', "b");
			Assert::IsFalse(checkIs_Appear);

			// Test if it returns False if a character does not contain within a long String
			checkIs_Appear = CodeParser::is_appeared('a', "movie");
			Assert::IsFalse(checkIs_Appear);

		}

	};
}