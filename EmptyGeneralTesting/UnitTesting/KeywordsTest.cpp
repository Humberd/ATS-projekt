#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/Keywords.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


TEST_CLASS(KeywordsTest) {
	TEST_METHOD(Keywords_isKeyword_Valid) {
		string keywords[] = {"procedure", "while", "if", "then", "else", "call"};

		for (auto keyword : keywords) {
			Assert::IsTrue(Keywords::isKeyword(keyword));
		}
	}

	TEST_METHOD(Keywords_isKeyword_Invalid) {
		string keywords[] = { "foo","bar"};

		for (auto keyword : keywords) {
			Assert::IsFalse(Keywords::isKeyword(keyword));
		}
	}
};