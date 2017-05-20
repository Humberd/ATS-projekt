#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QLexer.h"
#include "../SPA/QLexerException.h"
#include "../SPA/QTokenKeys.h"
#include "../SPA/DeclarationKeywords.h"
#include "../SPA/QuerySpecialCharacters.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(QLexerTest) {
	class ScanTestInstance {
	public:
		string input;
		string expectedResult;

		explicit ScanTestInstance(string input, string result) : input(input), expectedResult(result) {

		}
	};

	TEST_METHOD(QLexer_scanName_Valid) {
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
			Assert::IsTrue(instance->expectedResult == QLexer::scanName(instance->input.begin(), instance->input.end()));
			delete instance;
		}

		testList.clear();
	}

	TEST_METHOD(QLexer_scanName_Invalid) {
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
						QLexer::scanName(instance->input.begin(), instance->input.end());
					};

			Assert::ExpectException<QLexerException>(pointer);
			delete instance;
		}

		testList.clear();
	}

	TEST_METHOD(QLexer_scanInteger_Valid) {
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
		testList.push_back(new ScanTestInstance("23(", "23"));
		testList.push_back(new ScanTestInstance("23)", "23"));
		testList.push_back(new ScanTestInstance("23*", "23"));
		testList.push_back(new ScanTestInstance("23,", "23"));
		testList.push_back(new ScanTestInstance("23", "23"));
		testList.push_back(new ScanTestInstance("98\"12", "98"));

		for (auto instance : testList) {
			Assert::IsTrue(instance->expectedResult == QLexer::scanInteger(instance->input.begin(), instance->input.end()));
			delete instance;
		}

		testList.clear();
	}

	TEST_METHOD(QLexer_scanInteger_Invalid) {
		vector<ScanTestInstance*> testList;
		/*First param is a string we want to scan a INTEGER from, that will throw an exception*/
		testList.push_back(new ScanTestInstance("1foo", ""));
		testList.push_back(new ScanTestInstance(" 1Foo", ""));
		testList.push_back(new ScanTestInstance("_bar32", ""));
		testList.push_back(new ScanTestInstance("/nbar", ""));
		testList.push_back(new ScanTestInstance("\nbar", ""));
		testList.push_back(new ScanTestInstance("1.2", ""));
		testList.push_back(new ScanTestInstance("1:5", ""));
		testList.push_back(new ScanTestInstance("456f", ""));
		testList.push_back(new ScanTestInstance("27as 32", ""));
		testList.push_back(new ScanTestInstance("11/32", ""));
		testList.push_back(new ScanTestInstance("e 32", ""));


		for (auto instance : testList) {
			auto pointer = [instance] {
						QLexer::scanInteger(instance->input.begin(), instance->input.end());
					};

			Assert::ExpectException<QLexerException>(pointer);
			delete instance;
		}

		testList.clear();
	}

	TEST_METHOD(QLexer_parseDeclaration_Valid_1) {
		string sourceDeclarations = "procedure p;";

		vector<QLexerToken*> result = QLexer::parseDeclarations(sourceDeclarations);

		Assert::IsTrue(result.size() == 3);

		Assert::IsTrue(result.at(0)->getKey() == QTokenKeys::DECLARATION_KEYWORD);
		Assert::IsTrue(result.at(0)->getValue() == DeclarationKeywords::PROCEDURE);

		Assert::IsTrue(result.at(1)->getKey() == QTokenKeys::NAME);
		Assert::IsTrue(result.at(1)->getValue() == "p");

		Assert::IsTrue(result.at(2)->getKey() == QTokenKeys::SPECIAL_CHARACTER);
		Assert::IsTrue(result.at(2)->getValue() == QuerySpecialCharacters::SEMICOLON);

		for (auto item : result) {
			delete item;
		}
		result.clear();
	}

	TEST_METHOD(QLexer_parseDeclaration_Valid_2) {
		string sourceDeclarations = "while w; stmt  myStat ; if  ifstat;variable v;assign a; call baa; procedure p;";

		vector<QLexerToken*> result = QLexer::parseDeclarations(sourceDeclarations);

		vector<string> keywords;
		keywords.push_back(DeclarationKeywords::WHILE);
		keywords.push_back(DeclarationKeywords::STATEMENT);
		keywords.push_back(DeclarationKeywords::IF);
		keywords.push_back(DeclarationKeywords::VARIABLE);
		keywords.push_back(DeclarationKeywords::ASSIGN);
		keywords.push_back(DeclarationKeywords::CALL);
		keywords.push_back(DeclarationKeywords::PROCEDURE);

		vector<string> names;
		names.push_back("w");
		names.push_back("myStat");
		names.push_back("ifstat");
		names.push_back("v");
		names.push_back("a");
		names.push_back("baa");
		names.push_back("p");

		Assert::IsTrue(result.size() == keywords.size() * 3);

		for (int i = 0; i < keywords.size(); i++) {
			Assert::IsTrue(result.at(i * 3)->getKey() == QTokenKeys::DECLARATION_KEYWORD);
			Assert::IsTrue(result.at(i * 3)->getValue() == keywords.at(i));

			Assert::IsTrue(result.at(i * 3 + 1)->getKey() == QTokenKeys::NAME);
			Assert::IsTrue(result.at(i * 3 + 1)->getValue() == names.at(i));

			Assert::IsTrue(result.at(i * 3 + 2)->getKey() == QTokenKeys::SPECIAL_CHARACTER);
			Assert::IsTrue(result.at(i * 3 + 2)->getValue() == QuerySpecialCharacters::SEMICOLON);
		}
	}
};
