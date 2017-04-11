#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/StatementListNode.h"
#include "../SPA/RangeNumber.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(RangeNumberTest) {
	TEST_METHOD(RangeNumber_isWithinRangeInclusive_differentMinMax) {
		auto rangeNumber = new RangeNumber(1, 3);

		Assert::IsTrue(rangeNumber->isWithinRangeInclusive(1));
		Assert::IsTrue(rangeNumber->isWithinRangeInclusive(2));
		Assert::IsTrue(rangeNumber->isWithinRangeInclusive(3));

		delete rangeNumber;
	}

	TEST_METHOD(RangeNumber_isWithinRangeInclusive_infinities) {
		auto rangeNumber = new RangeNumber(INT32_MIN, INT32_MAX);

		Assert::IsTrue(rangeNumber->isWithinRangeInclusive(1));
		Assert::IsTrue(rangeNumber->isWithinRangeInclusive(2));
		Assert::IsTrue(rangeNumber->isWithinRangeInclusive(3));

		delete rangeNumber;
	}

	TEST_METHOD(RangeNumber_isWithinRangeInclusive_sameMinMax) {
		auto rangeNumber = new RangeNumber(2, 2);

		Assert::IsFalse(rangeNumber->isWithinRangeInclusive(1));
		Assert::IsTrue(rangeNumber->isWithinRangeInclusive(2));
		Assert::IsFalse(rangeNumber->isWithinRangeInclusive(3));

		delete rangeNumber;
	}

	TEST_METHOD(RangeNumber_isWithinRangeExclusive_differentMinMax) {
		auto rangeNumber = new RangeNumber(1, 3);

		Assert::IsFalse(rangeNumber->isWithinRangeExclusive(1));
		Assert::IsTrue(rangeNumber->isWithinRangeExclusive(2));
		Assert::IsFalse(rangeNumber->isWithinRangeExclusive(3));

		delete rangeNumber;
	}

	TEST_METHOD(RangeNumber_isWithinRangeExclusive_infinities) {
		auto rangeNumber = new RangeNumber(INT32_MIN, INT32_MAX);

		Assert::IsTrue(rangeNumber->isWithinRangeExclusive(1));
		Assert::IsTrue(rangeNumber->isWithinRangeExclusive(2));
		Assert::IsTrue(rangeNumber->isWithinRangeExclusive(3));

		delete rangeNumber;
	}

	TEST_METHOD(RangeNumber_isWithinRangeExclusive_sameMinMax) {
		auto rangeNumber = new RangeNumber(2, 2);

		Assert::IsFalse(rangeNumber->isWithinRangeExclusive(1));
		Assert::IsFalse(rangeNumber->isWithinRangeExclusive(2));
		Assert::IsFalse(rangeNumber->isWithinRangeExclusive(3));

		delete rangeNumber;
	}

};