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

		Lexer::mergeVectors(base, add);

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
		testList.push_back(new ScanTestInstance(" Foo ", "Foo"));
		testList.push_back(new ScanTestInstance(" foo bar", "foo"));
		testList.push_back(new ScanTestInstance("	foobar", "foobar"));
		testList.push_back(new ScanTestInstance(" foo32 ", "foo32"));
		testList.push_back(new ScanTestInstance("Foo Bar", "Foo"));
		testList.push_back(new ScanTestInstance("foo;", "foo"));
		testList.push_back(new ScanTestInstance("foobar*9", "foobar"));

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
		testList.push_back(new ScanTestInstance("	 453 ", "453"));
		testList.push_back(new ScanTestInstance(" 12 45", "12"));
		testList.push_back(new ScanTestInstance(" 123", "123"));
		testList.push_back(new ScanTestInstance("  1 32", "1"));
		testList.push_back(new ScanTestInstance("54 b3 ", "54"));
		testList.push_back(new ScanTestInstance("23;", "23"));
		testList.push_back(new ScanTestInstance("23{", "23"));
		testList.push_back(new ScanTestInstance("98+12", "98"));

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
		testList.push_back(new ScanTestInstance("27as 32", ""));
		testList.push_back(new ScanTestInstance("11/32", ""));
		testList.push_back(new ScanTestInstance("e 32", ""));


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

		Assert::IsTrue(result.at(0)->getKey() == "keyword");
		Assert::IsTrue(result.at(0)->getValue() == "procedure");

		Assert::IsTrue(result.at(1)->getKey() == "name");
		Assert::IsTrue(result.at(1)->getValue() == "Foo");

		Assert::IsTrue(result.at(2)->getKey() == "specialcharacter");
		Assert::IsTrue(result.at(2)->getValue() == "{");

		for (auto item : result) {
			delete item;
		}
		result.clear();
	}
};
