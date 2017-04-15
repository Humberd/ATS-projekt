#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/LexerToken.h"
#include "../SPA/Lexer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(LexerTest) {
	TEST_METHOD(Lexer_mergeVectors) {
		vector<LexerToken*> base;
		vector<LexerToken*> add;

		auto basePointer = &base;
		auto addPointer = &add;

		base.push_back(new LexerToken("foo", "bar"));
		add.push_back(new LexerToken("bla", "bla"));

		Lexer::mergeVectors(&base, &add);

		Assert::IsTrue(base.size() == 2);
		Assert::IsTrue(base.at(1) == add.at(0));

		for (auto token : base) {
			delete token;
		}
	}

	TEST_METHOD(Lexer_isIn) {
		Assert::IsFalse(Lexer::isIn('{', "foobar"));
		Assert::IsTrue(Lexer::isIn('{', "\{}/"));
		Assert::IsTrue(Lexer::isIn('{', "\\{}/"));
		Assert::IsTrue(Lexer::isIn('{', "/{}\\"));

		Assert::IsTrue(Lexer::isIn(' ', "foo bar"));
		Assert::IsFalse(Lexer::isIn(' ', "foobar\n"));
	}

	TEST_METHOD(Lexer_scanName) {
		string input = "foo";
		string::iterator iterator = input.begin();

		char character = *iterator;

		Logger::WriteMessage(string(1, character).c_str());

		Lexer::scanName(&iterator, &input.end());
	}
};