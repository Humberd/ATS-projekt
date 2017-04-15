#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/LexerToken.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(LexerTokenTest) {
	TEST_METHOD(LexerToken_constructor_string) {
		LexerToken* token = new LexerToken("foo", "bar");

		Assert::IsTrue(token->getKey() == "foo");
		Assert::IsTrue(token->getValue() == "bar");

		delete token;
	}

	TEST_METHOD(LexerToken_constructor_chars) {
		LexerToken* token = new LexerToken("foo", 'b');

		Assert::IsTrue(token->getKey() == "foo");
		Assert::IsTrue(token->getValue() == "b");

		delete token;
	}
};
