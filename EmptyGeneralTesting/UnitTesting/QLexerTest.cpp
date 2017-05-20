#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QLexer.h"
#include "../SPA/QLexerException.h"

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
};