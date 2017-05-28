#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/Spa.h"
#include "../SPA/SpaDataContainer.h"
#include "../SPA/TreeAnalyzer.h"
#include "../SPA/Next.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(NextTest) {
	Node* rootNode = nullptr;

	void checkEquality(vector<int>& values, vector<int>& expected) {
		Assert::IsTrue(values.size() == expected.size());

		for (unsigned int i = 0; i < values.size(); i++) {
			Assert::IsTrue(values.at(i) == expected.at(i));
		}
	}

	void checkEquality(vector<int>& values, int expected) {
		Assert::IsTrue(values.size() == 1);

		Assert::IsTrue(values.at(0) == expected);
	}

	void checkEquality(vector<int>& values) {
		Assert::IsTrue(values.size() == 0);
	}

	TEST_METHOD_INITIALIZE(Init) {
		rootNode = Spa::generateAstFromFile("../IntegrationTesting/NextTest.txt");
	}

	TEST_METHOD_CLEANUP(Cleanup) {
		delete rootNode;
	}

	TEST_METHOD(isNextTest) {
		SpaDataContainer* container = Spa::generateHelperTables(rootNode);
		auto sss = container->statementTable;
		Next* next = new Next(container->statementTable);
		bool a = next->isNext(new STMT(1), new STMT(2), false);
	}
};