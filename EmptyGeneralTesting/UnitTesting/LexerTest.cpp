#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/LexerToken.h"
#include "../SPA/Lexer.h"
#include <map>
#include "../SPA/LexerException.h"
#include "../SPA/TokenKeys.h"
#include "../SPA/Keywords.h"
#include "../SPA/SpecialCharacters.h"
#include "../SPA/Operators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(LexerTest) {
	TEST_METHOD(Lexer_mergeVectors) {
		vector<LexerToken*> base;
		vector<LexerToken*> add;

		base.push_back(new LexerToken("foo", "bar", 1));
		add.push_back(new LexerToken("bla", "bla", 1));

		Lexer::mergeVectors(base, add);

		Assert::IsTrue(base.size() == 2);
		Assert::IsTrue(base.at(1) == add.at(0));

		for (auto token : base) {
			delete token;
		}

		base.clear();
		add.clear();
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
		testList.push_back(new ScanTestInstance("44bar", ""));
		testList.push_back(new ScanTestInstance("3 bar", ""));
		testList.push_back(new ScanTestInstance("2", ""));


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

	TEST_METHOD(Lexer_parseLine_1) {
		string sourceLine = "procedure Foo {";

		vector<LexerToken*> result = Lexer::parseLine(sourceLine, 5);

		Assert::IsTrue(result.size() == 3);

		Assert::IsTrue(result.at(0)->getKey() == TokenKeys::KEYWORD);
		Assert::IsTrue(result.at(0)->getValue() == Keywords::PROCEDURE);
		Assert::IsTrue(result.at(0)->getFileLineNumber() == 5);

		Assert::IsTrue(result.at(1)->getKey() == TokenKeys::NAME);
		Assert::IsTrue(result.at(1)->getValue() == "Foo");
		Assert::IsTrue(result.at(1)->getFileLineNumber() == 5);

		Assert::IsTrue(result.at(2)->getKey() == TokenKeys::SPECIAL_CHARACTER);
		Assert::IsTrue(result.at(2)->getValue() == SpecialCharacters::OPEN_BRACE);
		Assert::IsTrue(result.at(2)->getFileLineNumber() == 5);

		for (auto item : result) {
			delete item;
		}
		result.clear();
	}

	TEST_METHOD(Lexer_parseLine_2) {
		string sourceLine = "	x= a+b * 15; ";

		vector<LexerToken*> result = Lexer::parseLine(sourceLine, 13);

		Assert::IsTrue(result.size() == 8);

		Assert::IsTrue(result.at(0)->getKey() == TokenKeys::NAME);
		Assert::IsTrue(result.at(0)->getValue() == "x");
		Assert::IsTrue(result.at(0)->getFileLineNumber() == 13);

		Assert::IsTrue(result.at(1)->getKey() == TokenKeys::SPECIAL_CHARACTER);
		Assert::IsTrue(result.at(1)->getValue() == SpecialCharacters::EQUALS_SIGN);
		Assert::IsTrue(result.at(1)->getFileLineNumber() == 13);

		Assert::IsTrue(result.at(2)->getKey() == TokenKeys::NAME);
		Assert::IsTrue(result.at(2)->getValue() == "a");
		Assert::IsTrue(result.at(2)->getFileLineNumber() == 13);

		Assert::IsTrue(result.at(3)->getKey() == TokenKeys::OPERATOR);
		Assert::IsTrue(result.at(3)->getValue() == Operators::PLUS_SIGN);
		Assert::IsTrue(result.at(3)->getFileLineNumber() == 13);

		Assert::IsTrue(result.at(4)->getKey() == TokenKeys::NAME);
		Assert::IsTrue(result.at(4)->getValue() == "b");
		Assert::IsTrue(result.at(4)->getFileLineNumber() == 13);

		Assert::IsTrue(result.at(5)->getKey() == TokenKeys::OPERATOR);
		Assert::IsTrue(result.at(5)->getValue() == Operators::TIMES_SIGN);
		Assert::IsTrue(result.at(5)->getFileLineNumber() == 13);

		Assert::IsTrue(result.at(6)->getKey() == TokenKeys::INTEGER);
		Assert::IsTrue(result.at(6)->getValue() == "15");
		Assert::IsTrue(result.at(6)->getFileLineNumber() == 13);

		Assert::IsTrue(result.at(7)->getKey() == TokenKeys::SPECIAL_CHARACTER);
		Assert::IsTrue(result.at(7)->getValue() == SpecialCharacters::SEMICOLON);
		Assert::IsTrue(result.at(7)->getFileLineNumber() == 13);

		for (auto item : result) {
			delete item;
		}
		result.clear();
	}

	TEST_METHOD(Lexer_parse) {
		vector<string> source;
		source.push_back("procedure q {");
		source.push_back("if x then {");
		source.push_back("z = x + 1; }");
		source.push_back("else {");
		source.push_back("x = z + x; } }");

		vector<LexerToken*> result = Lexer::parse(source);

		Assert::IsTrue(result.size() == 24);

		for (auto item : result) {
			delete item;
		}
		result.clear();
	}
};
