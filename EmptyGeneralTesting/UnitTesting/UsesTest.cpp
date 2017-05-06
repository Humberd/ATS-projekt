#include "stdafx.h"
#include <CppUnitTest.h>
#include "../SPA/Uses.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

//TEST_CLASS(UsesTest) {
//	//typedef string PROC;
//	//typedef int STMT;
//	//typedef string VAR;
//	//typedef int ASSIGN;
//	TEST_METHOD(Uses_getUsesASSIGN_Test) {
//		Uses *uses = new Uses();
//
//		uses->setUses(1, "a");
//		uses->setUses(1, "b");
//		uses->setUses(1, "c");
//
//		uses->setUses(2, "a1");
//		uses->setUses(2, "a2");
//		uses->setUses(2, "a3");
//
//		uses->setUses(3, "aa");
//		uses->setUses(3, "a");
//		uses->setUses(3, "ab");
//	}
//
//	TEST_METHOD(Uses_getUsesSTMT_Test) {
//		Uses *uses = new Uses();
//		STMT a1 = 1;
//
//		uses->setUses(a1, "a");
//	}
//
//	TEST_METHOD(Uses_getUsesPROC_Test) {
//		Uses *uses = new Uses();
//	}
//
//	TEST_METHOD(Uses_getUsedByASSIGN_Test) {
//		Uses *uses = new Uses();
//
//		uses->setUses(1, "a");
//		uses->setUses(1, "b");
//		uses->setUses(1, "c");
//
//		uses->setUses(2, "a1");
//		uses->setUses(2, "a2");
//		uses->setUses(2, "a3");
//
//		uses->setUses(3, "aa");
//		uses->setUses(3, "a");
//		uses->setUses(3, "ab");
//	}
//
//	TEST_METHOD(Uses_getUsesBySTMT_Test) {
//		Uses *uses = new Uses();
//	}
//
//	TEST_METHOD(Uses_getUsesByPROC_Test) {
//		Uses *uses = new Uses();
//	}
//
//	TEST_METHOD(Uses_isUsedASSIGN_Test) {
//		Uses *uses = new Uses();
//
//		uses->setUses(1, "a");
//		uses->setUses(1, "b");
//		uses->setUses(1, "c");
//
//		uses->setUses(2, "a1");
//		uses->setUses(2, "a2");
//		uses->setUses(2, "a3");
//
//		uses->setUses(3, "aa");
//		uses->setUses(3, "a");
//		uses->setUses(3, "ab");
//	}
//
//	TEST_METHOD(Uses_isUsedSTMT_Test) {
//		Uses *uses = new Uses();
//	}
//
//	TEST_METHOD(Uses_isUsedPROC_Test) {
//		Uses *uses = new Uses();
//	}
//
//};