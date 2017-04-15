#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/LexerToken.h"
#include "../SPA/Lexer.h"
#include <map>
#include "../SPA/LexerException.h"

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

	class ScanTestInstance {
	public:
		string input;
		string expectedResult;

		explicit ScanTestInstance(string input, string result): input(input), expectedResult(result) {

		}
	};

	TEST_METHOD(Lexer_scanName_IsChangingOutsideIterator) {
		string foo = "foo";
		auto itBegin = foo.begin();
		auto itEnd = foo.end();

		Lexer::scanName(itBegin, itEnd);

		Assert::IsTrue(itBegin == itEnd);
	}

	TEST_METHOD(Lexer_scanName_Valid) {
		vector<ScanTestInstance*> testList;
		/*First param is what we want to scan a NAME from, 
		 * Second is expected NAME from that string
		 */
		testList.push_back(new ScanTestInstance("foo", "foo"));
		testList.push_back(new ScanTestInstance(" foo", "foo"));
		testList.push_back(new ScanTestInstance(" Foo ", "foo"));
		testList.push_back(new ScanTestInstance(" foo bar", "foo"));
		testList.push_back(new ScanTestInstance(" f23p4 ", "f23p4"));


		for (auto instance : testList) {
			Assert::IsTrue(instance->expectedResult == Lexer::scanName(instance->input.begin(), instance->input.end()));
			delete instance;
		}

		testList.clear();
	}

	TEST_METHOD(Lexer_scanName_Invalid) {
		vector<ScanTestInstance*> testList;
		/*First param is a string we want to scan a NAME from, that will throw an exception*/
		testList.push_back(new ScanTestInstance("1foo", ""));
		testList.push_back(new ScanTestInstance(" 1Foo", ""));
		testList.push_back(new ScanTestInstance("_bar32", ""));
		testList.push_back(new ScanTestInstance("/nbar", ""));
		testList.push_back(new ScanTestInstance("\nbar", ""));


		for (auto instance : testList) {
			auto pointer = [instance] {
						Lexer::scanName(instance->input.begin(), instance->input.end());
					};

			Assert::ExpectException<LexerException>(pointer);
			delete instance;
		}

		testList.clear();
	}

	TEST_METHOD(Lexer_scanInteger_Valid) {
		vector<ScanTestInstance*> testList;
		/*First param is what we want to scan a INTEGER from,
		* Second is expected INTEGER from that string
		*/
		testList.push_back(new ScanTestInstance("2", "2"));
		testList.push_back(new ScanTestInstance(" 2", "2"));
		testList.push_back(new ScanTestInstance(" 453 ", "453"));
		testList.push_back(new ScanTestInstance(" 12 45", "12"));
		testList.push_back(new ScanTestInstance(" 0123456789 ", "0123456789"));


		for (auto instance : testList) {
			Assert::IsTrue(instance->expectedResult == Lexer::scanInteger(instance->input.begin(), instance->input.end()));
			delete instance;
		}

		testList.clear();
	}

	TEST_METHOD(Lexer_scanInteger_Invalid) {
		vector<ScanTestInstance*> testList;
		/*First param is a string we want to scan a INTEGER from, that will throw an exception*/
		testList.push_back(new ScanTestInstance("1foo", ""));
		testList.push_back(new ScanTestInstance(" 1Foo", ""));
		testList.push_back(new ScanTestInstance("_bar32", ""));
		testList.push_back(new ScanTestInstance("/nbar", ""));
		testList.push_back(new ScanTestInstance("\nbar", ""));
		testList.push_back(new ScanTestInstance("1.2", ""));
		testList.push_back(new ScanTestInstance("1,5", ""));
		testList.push_back(new ScanTestInstance("456f", ""));


		for (auto instance : testList) {
			auto pointer = [instance] {
						Lexer::scanInteger(instance->input.begin(), instance->input.end());
					};

			Assert::ExpectException<LexerException>(pointer);
			delete instance;
		}

		testList.clear();
	}

	TEST_METHOD(Lexer_parseLine) {
		string sourceLine = "procedure Foo {";

		vector<LexerToken*> result = Lexer::parseLine(sourceLine);

		Assert::IsTrue(result.size() == 3);
		Assert::IsTrue((*new LexerToken("name", "procedure")) == *result.at(0));
	}
};
