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
			checkIs_Duplicate = CodeParser::is_duplicate("a", sampleVector);
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

		//TEST_METHOD(CheckUsesTest) // Verify With Joshua
		//{
		//	std::vector<std::string> checkUsesOutput;
		//	std::vector<std::string> checkUsesExpectedOutPut;

		//	// Test if the ouput of CheckUses is the same as expected
		//	checkUsesExpectedOutPut.push_back("a,b");
		//	checkUsesOutput = CodeParser::checkUses("while", "x=a+b");
		//	Assert::AreSame(checkUsesExpectedOutPut[0], checkUsesOutput[0]);

		//	// Clear the vectors
		//	checkUsesExpectedOutPut.clear();
		//	checkUsesOutput.clear();

		//	// Test if the output of CheckUses is the same with duplicated variable
		//	checkUsesExpectedOutPut.push_back("a,b,c");
		//	checkUsesOutput = CodeParser::checkUses("while", "x=a*b+b+c");
		//	Assert::AreSame(checkUsesExpectedOutPut[0], checkUsesOutput[0]);

		//	// Clear the vectors
		//	checkUsesExpectedOutPut.clear();
		//	checkUsesOutput.clear();

		//	// Test if ouput of CheckUses is different as expected
		//	checkUsesExpectedOutPut.push_back("b,a");
		//	checkUsesOutput = CodeParser::checkUses("while", "x=a+b");
		//	Assert::AreSame(checkUsesExpectedOutPut[0], checkUsesOutput[0]);

		//}

		TEST_METHOD(CheckCompare_Nesting)
		{
			// create stack to test compare_nesting method
			std::stack <std::pair<int, string>> stackA;
			std::stack <std::pair<int, string>> stackB;
			bool checkOutput;

			// loading stackA with data
			stackA.push(make_pair(1, "a"));
			stackA.push(make_pair(1, "b"));
			stackA.push(make_pair(2, "c"));
			stackA.push(make_pair(3, "g"));

			// loading stackB with data
			stackB.push(make_pair(1, "a"));
			stackB.push(make_pair(1, "b"));
			stackB.push(make_pair(2, "c"));
			stackB.push(make_pair(3, "h"));

			// Comparing between stackA and stackB
			checkOutput = CodeParser::compare_nesting(stackA, stackB);

			// Test if compare_nesting returns true if there are difference between the stacks
			Assert::IsTrue(checkOutput);

			// Clearing a stack with ClearStack() method made for this purpose
			stackA = ClearStack();
			stackB = ClearStack();

			// loading stackA with data
			stackA.push(make_pair(1, "a"));
			stackA.push(make_pair(1, "b"));
			stackA.push(make_pair(2, "c"));
			stackA.push(make_pair(3, "g"));

			// loading stackB with data
			stackB.push(make_pair(1, "a"));
			stackB.push(make_pair(1, "b"));
			stackB.push(make_pair(2, "x"));
			stackB.push(make_pair(3, "g"));

			// Comparing between stackA and stackB
			checkOutput = CodeParser::compare_nesting(stackA, stackB);

			// Test if compare_nesting returns true if there are difference between the stacks
			Assert::IsTrue(checkOutput);

			// Clearing a stack with ClearStack() method made for this purpose
			stackA = ClearStack();
			stackB = ClearStack();

			// loading stackA with data
			stackA.push(make_pair(1, "a"));
			stackA.push(make_pair(1, "b"));
			stackA.push(make_pair(2, "c"));
			stackA.push(make_pair(3, "g"));

			// loading stackB with data
			stackB.push(make_pair(1, "a"));
			stackB.push(make_pair(2, "b"));
			stackB.push(make_pair(2, "c"));
			stackB.push(make_pair(3, "g"));

			// Comparing between stackA and stackB
			checkOutput = CodeParser::compare_nesting(stackA, stackB);

			// Test if compare_nesting returns true if there are difference between the stacks
			Assert::IsTrue(checkOutput);

			// Clearing a stack with ClearStack() method made for this purpose
			stackA = ClearStack();
			stackB = ClearStack();

			// Comparing between stackA and stackB 
			checkOutput = CodeParser::compare_nesting(stackA, stackB);

			// Test if compare_nesting returns false if both stacks are empty
			Assert::IsFalse(checkOutput);

			// Clearing a stack with ClearStack() method made for this purpose
			stackA = ClearStack();
			stackB = ClearStack();

			// Loading stackA with data
			stackA.push(make_pair(1, "h"));

			// Comparing between stackA and stackB
			checkOutput = CodeParser::compare_nesting(stackA, stackB);

			// Test if compare_nesting returns true if both stacks are of different sizes
			Assert::IsTrue(checkOutput);

			// Clearing a stack with ClearStack() method made for this purpose
			stackA = ClearStack();
			stackB = ClearStack();

			// Loading stackA with data
			stackA.push(make_pair(1, "h"));
			stackA.push(make_pair(1, "g"));

			// Loading stackB with data
			stackB.push(make_pair(1, "h"));

			// Comparing between stackA and stackB
			checkOutput = CodeParser::compare_nesting(stackA, stackB);

			// Test if compare_nesting returns true if both stacks are of different sizes
			Assert::IsTrue(checkOutput);

		}

		std::stack <std::pair<int, string>> ClearStack()
		{
			std::stack <std::pair<int, string>> theNewStack;
			return theNewStack;
		}

	};
}