#include "stdafx.h"
#include <CppUnitTest.h>
#include "../SPA/Modifies.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ModifiesTest) {

	TEST_METHOD(Modifies_setModifiesSTMT_Test) {
		auto modifies = new Modifies();

		modifies->setModifies(1, "a");
		modifies->setModifies(1, "b");
		modifies->setModifies(1, "c");
		modifies->setModifies(1, "d");

		modifies->setModifies(2, "a1");
		modifies->setModifies(2, "b1");
		modifies->setModifies(2, "c1");
		modifies->setModifies(2, "d1");

		Assert::IsTrue(4 == modifies->getModifiesBy(1).size());
		Assert::IsTrue(4 == modifies->getModifiesBy(2).size());
	}

	TEST_METHOD(Modifies_setModifiesPROC_Test) {
		auto modifies = new Modifies();

		modifies->setModifies("p1", "a");
		modifies->setModifies("p1", "b");
		modifies->setModifies("p1", "c");
		modifies->setModifies("p1", "d");

		modifies->setModifies("p2", "a1");
		modifies->setModifies("p2", "b1");
		modifies->setModifies("p2", "c1");
		modifies->setModifies("p2", "d1");

		Assert::IsTrue(4 == modifies->getModifiesBy("p1").size());
		Assert::IsTrue(4 == modifies->getModifiesBy("p2").size());
	}

	//typedef string PROC;
	//typedef int STMT;
	//typedef string VAR;
	//typedef int ASSIGN;
	TEST_METHOD(Modifies_getModifiesSTMT_Test) {
		auto modifies = new Modifies();

		modifies->setModifies(1, "a");
		modifies->setModifies(1, "b");
		modifies->setModifies(1, "c");
		modifies->setModifies(1, "d");

		modifies->setModifies(2, "a1");
		modifies->setModifies(2, "b1");
		modifies->setModifies(2, "c1");
		modifies->setModifies(2, "d1");

		modifies->setModifies(3, "a");
		modifies->setModifies(3, "b");
		modifies->setModifies(3, "c");
		modifies->setModifies(3, "d");

		Assert::IsTrue(1 == modifies->getModifiesSTMT("a1").size());
		Assert::IsTrue(2 == modifies->getModifiesSTMT("c").size());
	}

	TEST_METHOD(Modifies_getModifiesPROC_Test) {
		auto modifies = new Modifies();

		modifies->setModifies("p1", "a");
		modifies->setModifies("p1", "b");
		modifies->setModifies("p1", "c");
		modifies->setModifies("p1", "d");

		modifies->setModifies("p2", "a1");
		modifies->setModifies("p2", "b1");
		modifies->setModifies("p2", "c1");
		modifies->setModifies("p2", "d1");

		modifies->setModifies("p3", "a1");
		modifies->setModifies("p3", "b1");
		modifies->setModifies("p3", "c1");
		modifies->setModifies("p3", "d1");

		Assert::IsTrue(1 == modifies->getModifiesPROC("a").size());
		Assert::IsTrue(2 == modifies->getModifiesPROC("d1").size());
	}

	TEST_METHOD(Modifies_getModifiesBySTMT_Test) {
		auto modifies = new Modifies();

		modifies->setModifies(1, "a");
		modifies->setModifies(1, "b");
		modifies->setModifies(1, "c");
		modifies->setModifies(1, "d");

		modifies->setModifies(2, "a1");
		modifies->setModifies(2, "b1");
		modifies->setModifies(2, "c1");
		modifies->setModifies(2, "d1");

		modifies->setModifies(3, "a");
		modifies->setModifies(3, "b");
		modifies->setModifies(3, "c");
		modifies->setModifies(3, "d");

		Assert::IsTrue(4 == modifies->getModifiesBy(1).size());
		Assert::IsTrue(4 == modifies->getModifiesBy(2).size());
	}

	TEST_METHOD(Modifies_getModifiesByPROC_Test) {
		auto modifies = new Modifies();

		modifies->setModifies("p1", "a");
		modifies->setModifies("p1", "b");
		modifies->setModifies("p1", "c");
		modifies->setModifies("p1", "d");

		modifies->setModifies("p2", "a1");
		modifies->setModifies("p2", "b1");
		modifies->setModifies("p2", "c1");
		modifies->setModifies("p2", "d1");

		modifies->setModifies("p3", "a1");
		modifies->setModifies("p3", "b1");
		modifies->setModifies("p3", "c1");
		modifies->setModifies("p3", "d1");

		Assert::IsTrue(4 == modifies->getModifiesBy("p1").size());
		Assert::IsTrue(4 == modifies->getModifiesBy("p3").size());
	}

	TEST_METHOD(Modifies_isModifiesSTMT_Test) {
		auto modifies = new Modifies();

		modifies->setModifies(1, "a");
		modifies->setModifies(1, "b");
		modifies->setModifies(1, "c");
		modifies->setModifies(1, "d");

		modifies->setModifies(2, "a1");
		modifies->setModifies(2, "b1");
		modifies->setModifies(2, "c1");
		modifies->setModifies(2, "d1");

		modifies->setModifies(3, "a");
		modifies->setModifies(3, "b");
		modifies->setModifies(3, "c");
		modifies->setModifies(3, "d");

		Assert::IsTrue(modifies->isModifies(1,"a"));
		Assert::IsFalse(modifies->isModifies(2, "a"));
	}

	TEST_METHOD(Modifies_isModifiesPROC_Test) {
		auto modifies = new Modifies();

		modifies->setModifies("p1", "a");
		modifies->setModifies("p1", "b");
		modifies->setModifies("p1", "c");
		modifies->setModifies("p1", "d");

		modifies->setModifies("p2", "a1");
		modifies->setModifies("p2", "b1");
		modifies->setModifies("p2", "c1");
		modifies->setModifies("p2", "d1");

		modifies->setModifies("p3", "a1");
		modifies->setModifies("p3", "b1");
		modifies->setModifies("p3", "c1");
		modifies->setModifies("p3", "d1");

		Assert::IsTrue(modifies->isModifies("p1", "a"));
		Assert::IsFalse(modifies->isModifies("p3", "a"));
	}

};