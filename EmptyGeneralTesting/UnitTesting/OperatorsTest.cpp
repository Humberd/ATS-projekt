#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/Operators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


TEST_CLASS(OperatorsTest) {
	TEST_METHOD(Operators_isOperator_Valid) {
		string operators[] = {"+", "-", "*"};

		for (auto op : operators) {
			Assert::IsTrue(Operators::isOperator(op));
		}
	}

	TEST_METHOD(Operators_isOperator_Invalid) {
		string operators[] = {"/", ";","foo"};

		for (auto op : operators) {
			Assert::IsFalse(Operators::isOperator(op));
		}
	}
};
