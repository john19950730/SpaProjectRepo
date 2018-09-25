#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPKB)
	{
	public:
		TEST_CLASS_INITIALIZE(Setup)
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
			PKB::clearPKB();
			PKB::addProcedure("main");
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
			PKB::addParent(3, 4);
			PKB::addParent(3, 5);
			PKB::addParent(5, 6);
			PKB::addParent(5, 7);
			PKB::addUses(3, "x");
			PKB::addProcedureUses("main", "x");
			PKB::addUses(4, "y");
			PKB::addProcedureUses("main", "y");
			PKB::addUses(3, "y");
			PKB::addProcedureUses("main", "y"); //front-end parsing would have added duplicate, testing duplicate removal mechanism
			PKB::addUses(5, "y");
			PKB::addUses(3, "y"); // testing for non-procedure duplicate removal
			PKB::addUses(6, "x");
			PKB::addProcedureUses("main", "x");
			PKB::addUses(5, "x");
			PKB::addUses(3, "x"); // ^
			PKB::addUses(7, "y");
			PKB::addModifies(1, "x");
			PKB::addProcedureModifies("main", "x");
			PKB::addModifies(2, "y");
			PKB::addProcedureModifies("main", "y");
			PKB::addModifies(4, "y");
			PKB::addProcedureModifies("main", "y");
			PKB::addModifies(3, "y");
			PKB::addProcedureModifies("main", "y");
			PKB::addConstant(2, "2");
			PKB::addConstant(3, "0");
			PKB::addConstant(4, "1");
			PKB::addConstant(5, "5");
			PKB::addConstant(8, "0");
		}
		TEST_METHOD(Follows)
		{
			Assert::IsTrue(PKB::isFollows(1, 2, false)); //Follows(1, 2) is true
			Assert::IsTrue(PKB::isFollows(1, 2, true));
			Assert::IsTrue(PKB::isFollows(2, 3, true));
			Assert::IsFalse(PKB::isFollows(1, 3, false)); //Follows(1, 3) is false but...
			Assert::IsTrue(PKB::isFollows(1, 3, true)); //Follows*(1, 3) is true
			Assert::IsFalse(PKB::isFollows(2, 4, true)); //Follows*(2, 4) is false
			Assert::IsTrue(PKB::hasFollows(4, false)); //Follows(4, _) is true
			Assert::IsFalse(PKB::hasFollows(5, false)); //Follows(5, _) is false
			Assert::IsTrue(PKB::hasFollowedBy(8, false)); //Follows(_, 8) is true
			Assert::IsFalse(PKB::hasFollowedBy(7, false)); //Follows(_, 7) is false
			Assert::IsTrue(PKB::hasFollowsPair(false)); //Follows(_, _) is true

			vector<pair<unsigned int, unsigned int> > pairs = PKB::getAllFollowsPair("assign", "stmt", false);
			Assert::AreEqual(pairs.size(), (size_t)2); //Follows(a, s) should have 2 pairs
			Assert::IsTrue(pairs[0] == make_pair((unsigned int)2, (unsigned int)3)); //<2, 3>, and
			Assert::IsTrue(pairs[1] == make_pair((unsigned int)4, (unsigned int)5)); //<4, 5>

			vector<unsigned int> listA_ = PKB::getAllFollowedStmts("while", false);
			Assert::AreEqual(listA_.size(), (size_t)1); //Follows(w, _) should have 1 entry
			Assert::AreEqual(listA_[0], (unsigned int)3); // w = 3

			vector<unsigned int> list_B = PKB::getAllFollowsStmts("assign", false);
			Assert::AreEqual(list_B.size(), (size_t)2); //Follows(_, a) should have 2 entries
			Assert::AreEqual(list_B[0], (unsigned int)2); // a = 2 and
			Assert::AreEqual(list_B[1], (unsigned int)8); // a = 8

			vector<unsigned int> list1s = PKB::getAllStmtsThatFollows(1, "stmt", true);
			Assert::AreEqual(list1s.size(), (size_t)3); //Follows*(1, s) should have 3 entries
			Assert::IsTrue(list1s[0] == 2 && list1s[1] == 3 && list1s[2] == 8); // s = 2, 3, 8

			vector<unsigned int> lists2 = PKB::getAllStmtsFollowedBy("assign", 8, false);
			Assert::AreEqual(lists2.size(), (size_t)0); //Follows(a, 8) should have no entries
		}
		TEST_METHOD(Parent)
		{
			Assert::IsTrue(PKB::isParent(3, 4, false)); //Parent(3, 4) should be true
			Assert::IsFalse(PKB::isParent(3, 6, false)); //Parent(3, 6) should be false but...
			Assert::IsTrue(PKB::isParent(3, 6, true)); //Parent*(3, 6) should be true
			Assert::IsFalse(PKB::isParent(4, 5, false)); //Parent(4, 5) should be false
			Assert::IsTrue(PKB::hasChild(3, false)); //Parent(3, _) should be true
			Assert::IsFalse(PKB::hasChild(4, false)); //Parent(4, _) should be true
			Assert::IsTrue(PKB::hasParent(4, false)); //Parent(_, 4) should be true
			Assert::IsFalse(PKB::hasParent(3, false)); //Parent(3, _) should be false
			Assert::IsTrue(PKB::hasParentPair(false)); //Parent(_, _) should be true
			
			vector<pair<unsigned int, unsigned int> > pairs = PKB::getAllParentPair("stmt", "stmt", true);
			Assert::AreEqual(pairs.size(), (size_t)6); //Parent(stmt, stmt) should have 6 pairs as below
			Assert::IsTrue(find(pairs.begin(), pairs.end(), pair<unsigned int, unsigned int>(3, 4)) != pairs.end() &&
				find(pairs.begin(), pairs.end(), pair<unsigned int, unsigned int>(3, 5)) != pairs.end() &&
				find(pairs.begin(), pairs.end(), pair<unsigned int, unsigned int>(3, 6)) != pairs.end() &&
				find(pairs.begin(), pairs.end(), pair<unsigned int, unsigned int>(3, 7)) != pairs.end() &&
				find(pairs.begin(), pairs.end(), pair<unsigned int, unsigned int>(5, 6)) != pairs.end() &&
				find(pairs.begin(), pairs.end(), pair<unsigned int, unsigned int>(5, 7)) != pairs.end());
			
			vector<unsigned int> listw_ = PKB::getAllParentStmts("while", false);
			Assert::AreEqual(listw_.size(), (size_t)1); //Parent(w, _) should have only 1 stmt
			Assert::IsTrue(listw_[0] == 3);

			vector<unsigned int> list1p = PKB::getAllStmtsThatIsParentOf("while", 6, false);
			Assert::AreEqual(list1p.size(), (size_t)0); //Parent(w, 6) should return empty set
		}
		TEST_METHOD(Uses)
		{
			Assert::IsTrue(PKB::isUses(5, "y")); //Uses(5, "y") is true
			Assert::IsFalse(PKB::isUses(7, "x")); //Uses(7, "x") is false
			Assert::IsTrue(PKB::hasUses(3)); //Uses(3, _) is true
			Assert::IsFalse(PKB::hasUses(2)); //Uses(2, _) is false
			
			vector<pair<unsigned int, string> > pairs = PKB::getAllStmtUsesVariablePairs("while");
			Assert::AreEqual(pairs.size(), (size_t)2); //Uses(w, v) should have <3, "x"> and <3, "y">
			Assert::IsTrue(pairs[0] == pair<unsigned int, string>(3, "x") &&
				pairs[1] == pair<unsigned int, string>(3, "y"));

			vector<unsigned int> lists = PKB::getAllStmtsThatUsesVariable("stmt", "x");
			Assert::AreEqual(lists.size(), (size_t)3); //Uses(s, "x") should have 3, 6, 5
			Assert::IsTrue(lists[0] == 3 && lists[1] == 6 && lists[2] == 5);

			vector<pair<string, string> > procPairs = PKB::getAllProcedureUsesVariablePairs();
			Assert::AreEqual(procPairs.size(), (size_t)2); //Uses(p, v) should return <"main", "x"> and <"main", "y">
			Assert::IsTrue(procPairs[0] == make_pair(string("main"), string("x")) && procPairs[1] == make_pair(string("main"), string("y")));

			vector<string> procs = PKB::getAllProceduresThatUsesVariable("x");
			Assert::AreEqual(procs.size(), (size_t)1); //Uses(p, "x") should return "main"
			Assert::IsTrue(procs[0] == "main");

			Assert::IsTrue(PKB::hasProcedureUses("main")); //Uses("main", _) should be true
		}

		TEST_METHOD(Modifies)
		{
			Assert::IsTrue(PKB::isModifies(1, "x")); //Modifies(1, "x") is true
			Assert::IsFalse(PKB::isModifies(3, "x")); //Modifies(2, "x") is false
			Assert::IsTrue(PKB::hasModifies(3)); //Modifies(3, _) is true
			Assert::IsFalse(PKB::hasModifies(5)); //Modifies(5, _) is false

			vector<pair<unsigned int, string> > pairs = PKB::getAllStmtModifiesVariablePairs("stmt");
			Assert::AreEqual(pairs.size(), (size_t)4); //Modifies(s, v) should have <1, "x">, <2, "y">, <4, "y"> and <3, "y">
			Assert::IsTrue(pairs[0] == pair<unsigned int, string>(1, "x") &&
				pairs[1] == pair<unsigned int, string>(2, "y") &&
				pairs[2] == pair<unsigned int, string>(4, "y") &&
				pairs[3] == pair<unsigned int, string>(3, "y"));

			vector<unsigned int> lista_ = PKB::getAllStmtThatModifies("assign");
			Assert::AreEqual(lista_.size(), (size_t)2); //Modifies(a, _) should return 2 and 4
			Assert::IsTrue(lista_[0] == 2 && lista_[1] == 4);

			vector<unsigned int> listwx = PKB::getAllStmtThatModifiesVariable("while", "x");
			Assert::AreEqual(listwx.size(), (size_t)0); //Modifies(w, "x") returns nothing

			vector<string> procMs = PKB::getAllVariablesModifiedByProcedure("main");
			Assert::AreEqual(procMs.size(), (size_t)2); //Modifies("main", v) returns "x", "y"
			Assert::IsTrue(procMs[0] == string("x") && procMs[1] == string("y"));

			vector<string> noProc = PKB::getAllVariablesModifiedByProcedure("insignificant");
			Assert::AreEqual(noProc.size(), (size_t)0); //procedure non existant should return empty set
		}

		TEST_METHOD(ConstantPattern)
		{
			vector<unsigned int> lista0 = PKB::getAllAssignsWithConstant("0");
			Assert::AreEqual(lista0.size(), (size_t)1); //pattern a(_, _"0"_) should return 8
			Assert::IsTrue(lista0[0] == 8);

			Assert::IsTrue(PKB::isAssignmentUsesConstant(2, "2")); //a(2, _"2"_) should be 2, so true
			Assert::IsFalse(PKB::isAssignmentUsesConstant(4, "2")); //stmtNo #4 doesn't use 2, so false
			Assert::IsFalse(PKB::isAssignmentUsesConstant(3, "0")); //stmtNo #3 is not assignment, so false
			Assert::IsFalse(PKB::isAssignmentUsesConstant(6, "x")); //invalid and non-existent entry
		}
	};
}