#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPKB)
	{
	public:

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
			Assert::IsTrue(PKB::isFollows(1, 2, false));
		}

	};
}