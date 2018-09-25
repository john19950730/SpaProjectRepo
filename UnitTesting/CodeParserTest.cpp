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

		TEST_METHOD(CheckUsesTest) // Verify With Joshua
		{
			std::vector<std::string> checkUsesOutput;
			std::vector<std::string> checkUsesExpectedOutPut;
			int count;

			// Loading data to checkUsesExpectedOutput Vector & checkUsesOutput Vector
			checkUsesExpectedOutPut.push_back("x");
			checkUsesExpectedOutPut.push_back("a");
			checkUsesOutput = CodeParser::checkUses("while", "while(x!=0&&a!=0)",1);

			// Test if every item in the vectors are the same
			for (count = 0; count < checkUsesOutput.size(); count++)
			{
				Assert::AreEqual(checkUsesExpectedOutPut[count], checkUsesOutput[count]);
			}

			// Clear the vectors
			checkUsesExpectedOutPut.clear();
			checkUsesOutput.clear();

			// Loading data to checkUsesExpectedOutput Vector & checkUsesOutput Vector
			checkUsesExpectedOutPut.push_back("a");
			checkUsesExpectedOutPut.push_back("b");
			checkUsesExpectedOutPut.push_back("c");
			checkUsesOutput = CodeParser::checkUses("while", "while(a!=b && b!=c && c!=a && a!=1 || b!=2 || c!=3)",2);

			// Test if every item in the vectors are the same
			for (count = 0; count < checkUsesOutput.size(); count++)
			{
				Assert::AreEqual(checkUsesExpectedOutPut[count], checkUsesOutput[count]);
			}

			// Clear the vectors
			checkUsesExpectedOutPut.clear();
			checkUsesOutput.clear();

			// Loading data to checkUsesExpectedOutput Vector & checkUsesOutput Vector
			checkUsesExpectedOutPut.push_back("x");
			checkUsesExpectedOutPut.push_back("a");
			checkUsesOutput = CodeParser::checkUses("if", "if(x!=0&&a!=0)", 1);

			// Test if every item in the vectors are the same
			for (count = 0; count < checkUsesOutput.size(); count++)
			{
				Assert::AreEqual(checkUsesExpectedOutPut[count], checkUsesOutput[count]);
			}

			// Clear the vectors
			checkUsesExpectedOutPut.clear();
			checkUsesOutput.clear();

			// Loading data to checkUsesExpectedOutput Vector & checkUsesOutput Vector
			checkUsesExpectedOutPut.push_back("a");
			checkUsesExpectedOutPut.push_back("b");
			checkUsesExpectedOutPut.push_back("c");
			checkUsesOutput = CodeParser::checkUses("if", "if(a!=b && b!=c && c!=a && a!=1 || b!=2 || c!=3)", 2);

			// Test if every item in the vectors are the same
			for (count = 0; count < checkUsesOutput.size(); count++)
			{
				Assert::AreEqual(checkUsesExpectedOutPut[count], checkUsesOutput[count]);
			}

		}

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
			stackA = ClearPairStack();
			stackB = ClearPairStack();

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
			stackA = ClearPairStack();
			stackB = ClearPairStack();

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
			stackA = ClearPairStack();
			stackB = ClearPairStack();

			// Comparing between stackA and stackB 
			checkOutput = CodeParser::compare_nesting(stackA, stackB);

			// Test if compare_nesting returns false if both stacks are empty
			Assert::IsFalse(checkOutput);

			// Clearing a stack with ClearStack() method made for this purpose
			stackA = ClearPairStack();
			stackB = ClearPairStack();

			// Loading stackA with data
			stackA.push(make_pair(1, "h"));

			// Comparing between stackA and stackB
			checkOutput = CodeParser::compare_nesting(stackA, stackB);

			// Test if compare_nesting returns true if both stacks are of different sizes
			Assert::IsTrue(checkOutput);

			// Clearing a stack with ClearStack() method made for this purpose
			stackA = ClearPairStack();
			stackB = ClearPairStack();

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

		TEST_METHOD(CheckParentTest)
		{
			int expectOutput;
			stack < std::pair<int, string> > inputStack;

			// Load inputStack with relevant data
			inputStack.push(make_pair(0,"main"));
			inputStack.push(make_pair(4, "while"));
			inputStack.push(make_pair(7, "if"));
			inputStack.push(make_pair(0, "else"));

			// Load expectOutput with data using checkParent method
			expectOutput = CodeParser::checkParent(4, inputStack);

			// Test if the expectOutput returns 1 when found a parent in the stack
			Assert::AreEqual(expectOutput, 1);

			//Clear Stack
			inputStack = ClearIntPairStack();

			// Load inputStack with relevant data
			inputStack.push(make_pair(0, "main"));
			inputStack.push(make_pair(7, "if"));

			// Load expectOutput with data using checkParent method
			expectOutput = CodeParser::checkParent(4, inputStack);

			// Test if the expectOutput returns 1 when found a parent in the stack
			Assert::AreEqual(expectOutput, 1);

			//Clear Stack
			inputStack = ClearIntPairStack();

			// Load expectOutput with data using checkParent method
			expectOutput = CodeParser::checkParent(4, inputStack);

			// Test if the expectOutput returns 0 when stack is empty
			Assert::AreEqual(expectOutput, 0);

			//Clear Stack
			inputStack = ClearIntPairStack();

			// Load expectOutput with data using checkParent method
			inputStack.push(make_pair(0, "main"));
			expectOutput = CodeParser::checkParent(4, inputStack);

			// Test if the expectOutput returns 0 when stack has only parent
			Assert::AreEqual(expectOutput, 0);
		}

		TEST_METHOD(SplitWhileIfConditionTest)
		{
			std::vector<std::string> expectedVectorOutput;
			std::vector<std::string> methodVectorOutput;
			int count;

			// Load data for expectedVectorOutput & methodVectorOutput
			expectedVectorOutput.push_back("x");
			methodVectorOutput = CodeParser::splitWhileIfConditions("(x!=0)",2);

			// Test if methodVectorOutput are the same as expectedVectorOutput
			for (count = 0; count < methodVectorOutput.size(); count++)
			{
				Assert::AreEqual(expectedVectorOutput[count],methodVectorOutput[count]);
			}

			// Clear the vector
			expectedVectorOutput.clear();

			// Load data for expectedVectorOutput & methodVectorOutput
			expectedVectorOutput.push_back("x");
			expectedVectorOutput.push_back("y");
			expectedVectorOutput.push_back("z");
			expectedVectorOutput.push_back("a");
			methodVectorOutput = CodeParser::splitWhileIfConditions("(x!=0&&y<1||y==0&&z!=a||a==1)", 2);

			// Test if methodVectorOutput are the same as expectedVectorOutput
			for (count = 0; count < methodVectorOutput.size(); count++)
			{
				Assert::AreEqual(expectedVectorOutput[count], methodVectorOutput[count]);
			}
		}

		TEST_METHOD(splitTest) 
		{
			std::vector<std::string> expectedVectorOutput;
			std::vector<std::string> methodVectorOutput;
			int count;
			int vectorSize;

			// Load data for expectedVectorOutput & methodVectorOutput
			expectedVectorOutput.push_back("a");
			expectedVectorOutput.push_back("b");
			expectedVectorOutput.push_back("c");
			expectedVectorOutput.push_back("d");
			methodVectorOutput = CodeParser::splitWhileIfConditions("a*(b+c)/d", 2);

			// Test if methodVectorOutput are the same as expectedVectorOutput
			for (count = 0; count < methodVectorOutput.size(); count++)
			{
				Assert::AreEqual(expectedVectorOutput[count], methodVectorOutput[count]);
			}

			// Clearing Vector
			expectedVectorOutput.clear();

			// Load data for expectedVectorOutput & methodVectorOutput
			expectedVectorOutput.push_back("a");
			expectedVectorOutput.push_back("b");
			expectedVectorOutput.push_back("c");
			expectedVectorOutput.push_back("d");
			methodVectorOutput = CodeParser::splitWhileIfConditions("a*b+c/d", 2);

			// Test if methodVectorOutput are the same as expectedVectorOutput
			for (count = 0; count < methodVectorOutput.size(); count++)
			{
				Assert::AreEqual(expectedVectorOutput[count], methodVectorOutput[count]);
			}

			// Clearing Vector
			expectedVectorOutput.clear();

			// Load data for expectedVectorOutput & methodVectorOutput
			expectedVectorOutput.push_back("a");
			expectedVectorOutput.push_back("b");
			expectedVectorOutput.push_back("c");
			expectedVectorOutput.push_back("d");
			methodVectorOutput = CodeParser::splitWhileIfConditions("a*b+c%d+1", 2);

			// Test if methodVectorOutput are the same as expectedVectorOutput
			for (count = 0; count < methodVectorOutput.size(); count++)
			{
				Assert::AreEqual(expectedVectorOutput[count], methodVectorOutput[count]);
			}
			// Clearing Vector
			expectedVectorOutput.clear();

			// Load data for expectedVectorOutput & methodVectorOutput
			expectedVectorOutput.push_back("a");
			expectedVectorOutput.push_back("b");
			expectedVectorOutput.push_back("c");
			expectedVectorOutput.push_back("d");
			methodVectorOutput = CodeParser::splitWhileIfConditions("a%b%c%(d+1)", 2);

			// Test if methodVectorOutput are the same as expectedVectorOutput
			for (count = 0; count < methodVectorOutput.size(); count++)
			{
				Assert::AreEqual(expectedVectorOutput[count], methodVectorOutput[count]);
			}

			// Clearing Vector
			expectedVectorOutput.clear();

			// Load data for expectedVectorOutput & methodVectorOutput
			methodVectorOutput = CodeParser::splitWhileIfConditions("5%1+10*100", 2);
			vectorSize = methodVectorOutput.size();
			// Test if methodVectorOutput are the same as expectedVectorOutput when both are supposed to be empty
			Assert::AreEqual(vectorSize, 0);

		}

		std::stack <std::pair<int, string>> ClearPairStack()
		{
			std::stack <std::pair<int, string>> theNewStack;
			return theNewStack;
		}

		stack < std::pair<int, string> > ClearIntPairStack()
		{
			stack < std::pair<int, string> > theNewStack;
			return theNewStack;
		}

	};
}