#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/SpecialCharacters.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


TEST_CLASS(SpecialCharactersTest) {
	TEST_METHOD(SpecialCharacters_isSpecialCharacter_Valid) {
		string specialCharacters[] = {"{","}",";","="};

		for (auto specChar : specialCharacters) {
			Assert::IsTrue(SpecialCharacters::isSpecialCharacter(specChar));
		}
	}

	TEST_METHOD(SpecialCharacters_isSpecialCharacter_Invalid) {
		string specialCharacters[] = {"foo", "bar", "+","-","/","[","]"};

		for (auto specChar : specialCharacters) {
			Assert::IsFalse(SpecialCharacters::isSpecialCharacter(specChar));
		}
	}
};
