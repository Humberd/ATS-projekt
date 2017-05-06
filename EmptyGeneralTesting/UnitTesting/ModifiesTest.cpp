#include "stdafx.h"
#include <CppUnitTest.h>
#include "../SPA/Modifies.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ModifiesTest) {

	TEST_METHOD(Modifies_setModifiesSTMT_Test) {
		auto modifies = new Modifies();
		
		modifies->setModifies(new STMT(1), new VAR("a"));
		modifies->setModifies(new STMT(1), new VAR("b"));
		modifies->setModifies(new STMT(1), new VAR("c"));
		modifies->setModifies(new STMT(1), new VAR("d"));

		modifies->setModifies(new STMT(2), new VAR("a1"));
		modifies->setModifies(new STMT(2), new VAR("b1"));
		modifies->setModifies(new STMT(2), new VAR("c1"));
		modifies->setModifies(new STMT(2), new VAR("d1"));

		Assert::IsTrue(4 == modifies->getModifiesBy(new STMT(1)).size());
		Assert::IsTrue(4 == modifies->getModifiesBy(new STMT(2)).size());
	}

	TEST_METHOD(Modifies_setModifiesPROC_Test) {
		auto modifies = new Modifies();

		modifies->setModifies(new PROC("p1"), new VAR("a"));
		modifies->setModifies(new PROC("p1"), new VAR("b"));
		modifies->setModifies(new PROC("p1"), new VAR("c"));
		modifies->setModifies(new PROC("p1"), new VAR("d"));

		modifies->setModifies(new PROC("p2"), new VAR("a1"));
		modifies->setModifies(new PROC("p2"), new VAR("b1"));
		modifies->setModifies(new PROC("p2"), new VAR("c1"));
		modifies->setModifies(new PROC("p2"), new VAR("d1"));

		Assert::IsTrue(4 == modifies->getModifiesBy(new PROC("p1")).size());
		Assert::IsTrue(4 == modifies->getModifiesBy(new PROC("p2")).size());
	}

	TEST_METHOD(Modifies_getModifiesSTMT_Test) {
		auto modifies = new Modifies();

		modifies->setModifies(new STMT(1), new VAR("a"));
		modifies->setModifies(new STMT(1), new VAR("b"));
		modifies->setModifies(new STMT(1), new VAR("c"));
		modifies->setModifies(new STMT(1), new VAR("d"));

		modifies->setModifies(new STMT(2), new VAR("a1"));
		modifies->setModifies(new STMT(2), new VAR("b1"));
		modifies->setModifies(new STMT(2), new VAR("c1"));
		modifies->setModifies(new STMT(2), new VAR("d1"));

		modifies->setModifies(new STMT(3), new VAR("a"));
		modifies->setModifies(new STMT(3), new VAR("b"));
		modifies->setModifies(new STMT(3), new VAR("c"));
		modifies->setModifies(new STMT(3), new VAR("d"));

		Assert::IsTrue(1 == modifies->getModifiesSTMT(new VAR("a1")).size());
		Assert::IsTrue(2 == modifies->getModifiesSTMT(new VAR("c")).size());
	}

	TEST_METHOD(Modifies_getModifiesPROC_Test) {
		auto modifies = new Modifies();

		modifies->setModifies(new PROC("p1"), new VAR("a"));
		modifies->setModifies(new PROC("p1"), new VAR("b"));
		modifies->setModifies(new PROC("p1"), new VAR("c"));
		modifies->setModifies(new PROC("p1"), new VAR("d"));

		modifies->setModifies(new PROC("p2"), new VAR("a1"));
		modifies->setModifies(new PROC("p2"), new VAR("b1"));
		modifies->setModifies(new PROC("p2"), new VAR("c1"));
		modifies->setModifies(new PROC("p2"), new VAR("d1"));

		modifies->setModifies(new PROC("p3"), new VAR("a1"));
		modifies->setModifies(new PROC("p3"), new VAR("b1"));
		modifies->setModifies(new PROC("p3"), new VAR("c1"));
		modifies->setModifies(new PROC("p3"), new VAR("d1"));

		bool a = modifies->getModifiesPROC(new VAR("a")).size();
		bool b = modifies->getModifiesPROC(new VAR("d1")).size();

		Assert::IsTrue(1 == modifies->getModifiesPROC(new VAR("a")).size());
		Assert::IsTrue(2 == modifies->getModifiesPROC(new VAR("d1")).size());
	}

	TEST_METHOD(Modifies_getModifiesBySTMT_Test) {
		auto modifies = new Modifies();

		modifies->setModifies(new STMT(1), new VAR("a"));
		modifies->setModifies(new STMT(1), new VAR("b"));
		modifies->setModifies(new STMT(1), new VAR("c"));
		modifies->setModifies(new STMT(1), new VAR("d"));

		modifies->setModifies(new STMT(2), new VAR("a1"));
		modifies->setModifies(new STMT(2), new VAR("b1"));
		modifies->setModifies(new STMT(2), new VAR("c1"));
		modifies->setModifies(new STMT(2), new VAR("d1"));

		modifies->setModifies(new STMT(3), new VAR("a"));
		modifies->setModifies(new STMT(3), new VAR("b"));
		modifies->setModifies(new STMT(3), new VAR("c"));
		modifies->setModifies(new STMT(3), new VAR("d"));

		Assert::IsTrue(4 == modifies->getModifiesBy(new STMT(1)).size());
		Assert::IsTrue(4 == modifies->getModifiesBy(new STMT(2)).size());
	}

	TEST_METHOD(Modifies_getModifiesByPROC_Test) {
		auto modifies = new Modifies();

		modifies->setModifies(new PROC("p1"), new VAR("a"));
		modifies->setModifies(new PROC("p1"), new VAR("b"));
		modifies->setModifies(new PROC("p1"), new VAR("c"));
		modifies->setModifies(new PROC("p1"), new VAR("d"));

		modifies->setModifies(new PROC("p2"), new VAR("a1"));
		modifies->setModifies(new PROC("p2"), new VAR("b1"));
		modifies->setModifies(new PROC("p2"), new VAR("c1"));
		modifies->setModifies(new PROC("p2"), new VAR("d1"));

		modifies->setModifies(new PROC("p3"), new VAR("a1"));
		modifies->setModifies(new PROC("p3"), new VAR("b1"));
		modifies->setModifies(new PROC("p3"), new VAR("c1"));
		modifies->setModifies(new PROC("p3"), new VAR("d1"));

		Assert::IsTrue(4 == modifies->getModifiesBy(new PROC("p1")).size());
		Assert::IsTrue(4 == modifies->getModifiesBy(new PROC("p3")).size());
	}

	TEST_METHOD(Modifies_isModifiesSTMT_Test) {
		auto modifies = new Modifies();

		modifies->setModifies(new STMT(1), new VAR("a"));
		modifies->setModifies(new STMT(1), new VAR("b"));
		modifies->setModifies(new STMT(1), new VAR("c"));
		modifies->setModifies(new STMT(1), new VAR("d"));

		modifies->setModifies(new STMT(2), new VAR("a1"));
		modifies->setModifies(new STMT(2), new VAR("b1"));
		modifies->setModifies(new STMT(2), new VAR("c1"));
		modifies->setModifies(new STMT(2), new VAR("d1"));

		modifies->setModifies(new STMT(3), new VAR("a"));
		modifies->setModifies(new STMT(3), new VAR("b"));
		modifies->setModifies(new STMT(3), new VAR("c"));
		modifies->setModifies(new STMT(3), new VAR("d"));

		Assert::IsTrue(modifies->isModifies(1,new VAR("a")));
		Assert::IsFalse(modifies->isModifies(2, new VAR("a")));
	}

	TEST_METHOD(Modifies_isModifiesPROC_Test) {
		auto modifies = new Modifies();

		modifies->setModifies(new PROC("p1"), new VAR("a"));
		modifies->setModifies(new PROC("p1"), new VAR("b"));
		modifies->setModifies(new PROC("p1"), new VAR("c"));
		modifies->setModifies(new PROC("p1"), new VAR("d"));

		modifies->setModifies(new PROC("p2"), new VAR("a1"));
		modifies->setModifies(new PROC("p2"), new VAR("b1"));
		modifies->setModifies(new PROC("p2"), new VAR("c1"));
		modifies->setModifies(new PROC("p2"), new VAR("d1"));

		modifies->setModifies(new PROC("p3"), new VAR("a1"));
		modifies->setModifies(new PROC("p3"), new VAR("b1"));
		modifies->setModifies(new PROC("p3"), new VAR("c1"));
		modifies->setModifies(new PROC("p3"), new VAR("d1"));

		Assert::IsTrue(modifies->isModifies("p1", new VAR("a")));
		Assert::IsFalse(modifies->isModifies("p3", new VAR("a")));
	}

};