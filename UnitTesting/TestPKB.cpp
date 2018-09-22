#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPKB)
	{
	public:
		TEST_METHOD(Utility)
		{
			/*	Using sample (invalid) SIMPLE Program as follows for reference:
			procedure main {
		1		read x;
		2		while (x > 0) {
		3			y = y + 1;
		4			if (y > 5) {
		5				print x;
					} else {
		6				call main;
					}
				}
		7		y = 0;
			} */
			// Populating PKB with relevant data
			PKB::addRead(1);
			PKB::addWhile(2);
			PKB::addAssign(3);
			PKB::addIf(4);
			PKB::addPrint(5);
			PKB::addCall(6);
			PKB::addAssign(7);
			vector<unsigned int> reads = PKB::getReads();
			Assert::IsFalse(find(reads.begin(), reads.end(), (unsigned int) 1) == reads.end());
			Assert::AreEqual(PKB::getSynonymTypeOfStmt(1), string("read"));
		}
		TEST_METHOD(Follows)
		{
			/*	Using sample SIMPLE Program as follows for reference:
			procedure main {
		1		read x;
		2		y = 2;
		3		while (x > 0) {
		4			y = y + 1;
		5			if (y > 5) {
		6				print x;
					} else {
		7				print y;
					}
				}
		8		y = 0;
			} */
			// Populating PKB with relevant data
			PKB::addRead(1);
			PKB::addAssign(2);
			PKB::addWhile(3);
			PKB::addAssign(4);
			PKB::addIf(5);
			PKB::addPrint(6);
			PKB::addPrint(7);
			PKB::addAssign(8);
			PKB::addFollows(1, 2);
			PKB::addFollows(2, 3);
			PKB::addFollows(4, 5);
			PKB::addFollows(3, 8);
			
			// Tests
			Assert::IsTrue(PKB::isFollows(1, 2, false)); //Follows(1, 2) is true
			Assert::IsFalse(PKB::isFollows(2, 4, false)); //Follows(2, 4) is false
			Assert::IsTrue(PKB::hasFollows(4, false)); //Follows(4, _) is true
			Assert::IsFalse(PKB::hasFollows(5, false)); //Follows(5, _) is false
			Assert::IsTrue(PKB::hasFollowedBy(8, false)); //Follows(_, 8) is true
			Assert::IsFalse(PKB::hasFollowedBy(7, false)); //Follows(_, 7) is false
		}

	};
}