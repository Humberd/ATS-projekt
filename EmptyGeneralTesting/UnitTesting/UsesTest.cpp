#include "stdafx.h"
#include <CppUnitTest.h>
#include "../SPA/Uses.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(UsesTest) {
	//typedef string PROC;
	//typedef int STMT;
	//typedef string VAR;
	//typedef int ASSIGN;
	TEST_METHOD(Uses_getUsesASSIGN_Test) {
		Uses *uses = new Uses();

		uses->setUses(new ASSIGN(1), new VAR("a"));
		uses->setUses(new ASSIGN(1), new VAR("b"));
		uses->setUses(new ASSIGN(1), new VAR("c"));

		uses->setUses(new ASSIGN(2), new VAR("a1"));
		uses->setUses(new ASSIGN(2), new VAR("a2"));
		uses->setUses(new ASSIGN(2), new VAR("a3"));

		uses->setUses(new ASSIGN(3), new VAR("aa"));
		uses->setUses(new ASSIGN(3), new VAR("a"));
		uses->setUses(new ASSIGN(3), new VAR("ab"));

		Assert::IsTrue(3 == uses->getUses(new ASSIGN(1)).size());
		Assert::IsTrue(3 == uses->getUses(new ASSIGN(2)).size());
		Assert::IsTrue(3 == uses->getUses(new ASSIGN(3)).size());
	}

	TEST_METHOD(Uses_getUsesSTMT_Test) {
		Uses *uses = new Uses();
		
		uses->setUses(new STMT(1), new VAR("a"));
		uses->setUses(new STMT(1), new VAR("b"));
		uses->setUses(new STMT(1), new VAR("c"));

		uses->setUses(new STMT(2), new VAR("a"));
		uses->setUses(new STMT(2), new VAR("a2"));
		uses->setUses(new STMT(2), new VAR("a3"));

		uses->setUses(new STMT(3), new VAR("aa"));
		uses->setUses(new STMT(3), new VAR("a"));
		uses->setUses(new STMT(3), new VAR("ab"));

		Assert::IsTrue(3 == uses->getUses(new STMT(1)).size());
		Assert::IsTrue(3 == uses->getUses(new STMT(2)).size());
		Assert::IsTrue(3 == uses->getUses(new STMT(3)).size());
	}

	TEST_METHOD(Uses_getUsesPROC_Test) {
		Uses *uses = new Uses();

		uses->setUses(new PROC("1"), new VAR("a"));
		uses->setUses(new PROC("1"), new VAR("b"));
		uses->setUses(new PROC("1"), new VAR("c"));

		uses->setUses(new PROC("2"), new VAR("a"));
		uses->setUses(new PROC("2"), new VAR("a2"));
		uses->setUses(new PROC("2"), new VAR("a3"));

		uses->setUses(new PROC("3"), new VAR("aa"));
		uses->setUses(new PROC("3"), new VAR("a"));
		uses->setUses(new PROC("3"), new VAR("ab"));

		Assert::IsTrue(3 == uses->getUses(new PROC("1")).size());
		Assert::IsTrue(3 == uses->getUses(new PROC("2")).size());
		Assert::IsTrue(3 == uses->getUses(new PROC("3")).size());
	}

	TEST_METHOD(Uses_getUsedByASSIGN_Test) {
		Uses *uses = new Uses();

		uses->setUses(new ASSIGN(1), new VAR("a"));
		uses->setUses(new ASSIGN(1), new VAR("b"));
		uses->setUses(new ASSIGN(1), new VAR("c"));

		uses->setUses(new ASSIGN(2), new VAR("a"));
		uses->setUses(new ASSIGN(2), new VAR("a2"));
		uses->setUses(new ASSIGN(2), new VAR("a3"));

		uses->setUses(new ASSIGN(3), new VAR("aa"));
		uses->setUses(new ASSIGN(3), new VAR("a"));
		uses->setUses(new ASSIGN(3), new VAR("ab"));

		Assert::IsTrue(3 == uses->getUsedByASSIGN(new VAR("a")).size());
		Assert::IsTrue(1 == uses->getUsedByASSIGN(new VAR("c")).size());
	}

	TEST_METHOD(Uses_getUsesBySTMT_Test) {
		Uses *uses = new Uses();

		uses->setUses(new STMT(1), new VAR("a"));
		uses->setUses(new STMT(1), new VAR("b"));
		uses->setUses(new STMT(1), new VAR("c"));

		uses->setUses(new STMT(2), new VAR("a"));
		uses->setUses(new STMT(2), new VAR("a2"));
		uses->setUses(new STMT(2), new VAR("a3"));

		uses->setUses(new STMT(3), new VAR("aa"));
		uses->setUses(new STMT(3), new VAR("a"));
		uses->setUses(new STMT(3), new VAR("ab"));

		Assert::IsTrue(3 == uses->getUsesBySTMT(new VAR("a")).size());
		Assert::IsTrue(1 == uses->getUsesBySTMT(new VAR("c")).size());
	}

	TEST_METHOD(Uses_getUsesByPROC_Test) {
		Uses *uses = new Uses();

		uses->setUses(new PROC("1"), new VAR("a"));
		uses->setUses(new PROC("1"), new VAR("b"));
		uses->setUses(new PROC("1"), new VAR("c"));

		uses->setUses(new PROC("2"), new VAR("a"));
		uses->setUses(new PROC("2"), new VAR("a2"));
		uses->setUses(new PROC("2"), new VAR("a3"));

		uses->setUses(new PROC("3"), new VAR("aa"));
		uses->setUses(new PROC("3"), new VAR("a"));
		uses->setUses(new PROC("3"), new VAR("ab"));

		Assert::IsTrue(3 == uses->getUsesByPROC(new VAR("a")).size());
		Assert::IsTrue(1 == uses->getUsesByPROC(new VAR("c")).size());
	}

	TEST_METHOD(Uses_isUsedASSIGN_Test) {
		Uses *uses = new Uses();
	}

	TEST_METHOD(Uses_isUsedSTMT_Test) {
		Uses *uses = new Uses();
	}

	TEST_METHOD(Uses_isUsedPROC_Test) {
		Uses *uses = new Uses();
	}

};