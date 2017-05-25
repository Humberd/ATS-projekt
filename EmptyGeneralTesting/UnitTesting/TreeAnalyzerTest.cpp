#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/Spa.h"
#include "../SPA/SpaDataContainer.h"
#include "../SPA/TreeAnalyzer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(TreeAnalyzerTest) {
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
		rootNode = Spa::generateAstFromFile("../IntegrationTesting/Source2.txt");
	}

	TEST_METHOD_CLEANUP(Cleanup) {
		delete rootNode;
	}

	TEST_METHOD(TreeAnalyzer_analyzeParentsTable) {
		TreeAnalyzer treeAnalyzer;

		map<int, vector<int>> parentsTable = treeAnalyzer.analyzeParentsTable(rootNode);

		Assert::IsTrue(parentsTable.size() == 6);

		vector<int> expRes9 = {10,11,14,15,16,17};
		this->checkEquality(parentsTable.at(9), expRes9);

		vector<int> expRes11 = {12,13};
		this->checkEquality(parentsTable.at(11), expRes11);

		vector<int> expRes19 = {20,21,22};
		this->checkEquality(parentsTable.at(19), expRes19);

		vector<int> expRes24 = {25,26};
		this->checkEquality(parentsTable.at(24), expRes24);

		vector<int> expRes28 = {29};
		this->checkEquality(parentsTable.at(28), expRes28);

		vector<int> expRes29 = {30,31};
		this->checkEquality(parentsTable.at(29), expRes29);
	}

	TEST_METHOD(TreeAnalyzer_analyzeFollowsTable) {
		TreeAnalyzer treeAnalyzer;

		map<int, vector<int>> followsTable = treeAnalyzer.analyzeFollowsTable(rootNode);

		this->checkEquality(followsTable.at(1), 2);
		this->checkEquality(followsTable.at(2), 3);
		this->checkEquality(followsTable.at(3), 4);
		this->checkEquality(followsTable.at(4), 5);
		this->checkEquality(followsTable.at(5), 6);
		this->checkEquality(followsTable.at(6), 7);
		this->checkEquality(followsTable.at(7), 8);
		this->checkEquality(followsTable.at(8), 9);
		this->checkEquality(followsTable.at(9), 18);
		this->checkEquality(followsTable.at(10), 11);
		this->checkEquality(followsTable.at(11), 14);
		this->checkEquality(followsTable.at(12), 13);
		this->checkEquality(followsTable.at(13));
		this->checkEquality(followsTable.at(14));
		this->checkEquality(followsTable.at(15), 16);
		this->checkEquality(followsTable.at(16), 17);
		this->checkEquality(followsTable.at(17));
		this->checkEquality(followsTable.at(18));
		this->checkEquality(followsTable.at(19), 23);
		this->checkEquality(followsTable.at(20), 21);
		this->checkEquality(followsTable.at(21), 22);
		this->checkEquality(followsTable.at(22));
		this->checkEquality(followsTable.at(23));
		this->checkEquality(followsTable.at(24), 27);
		this->checkEquality(followsTable.at(25));
		this->checkEquality(followsTable.at(26));
		this->checkEquality(followsTable.at(27));
		this->checkEquality(followsTable.at(28));
		this->checkEquality(followsTable.at(29));
		this->checkEquality(followsTable.at(30));
		this->checkEquality(followsTable.at(31));
	}
	
	TEST_METHOD(TreeAnalyzer_analyzeProceduresTable) {
		TreeAnalyzer treeAnalyzer;

		vector<Node*> proceduresTable = treeAnalyzer.analyzeProceduresTable(rootNode);

		Assert::IsTrue(proceduresTable.size() == 4);
		Assert::IsTrue(dynamic_cast<ProcedureNode*>(proceduresTable.at(0))->getName() == "Planet");
		Assert::IsTrue(dynamic_cast<ProcedureNode*>(proceduresTable.at(1))->getName() == "Earth");
		Assert::IsTrue(dynamic_cast<ProcedureNode*>(proceduresTable.at(2))->getName() == "Moon");
		Assert::IsTrue(dynamic_cast<ProcedureNode*>(proceduresTable.at(3))->getName() == "Sun");
	}

	TEST_METHOD(TreeAnalyzer_analyzeCallsTable) {
		TreeAnalyzer treeAnalyzer;

		map<string, vector<string>> callsTable = treeAnalyzer.analyzeCallsTable(rootNode);

		Assert::IsTrue(callsTable.size() == 4);
		Assert::IsTrue(callsTable.at("Planet").size() == 3);
		Assert::IsTrue(callsTable.at("Planet").at(0) == "Earth");
		Assert::IsTrue(callsTable.at("Planet").at(1) == "Moon");
		Assert::IsTrue(callsTable.at("Planet").at(2) == "Sun");

		Assert::IsTrue(callsTable.at("Earth").size() == 1);
		Assert::IsTrue(callsTable.at("Earth").at(0) == "Sun");

		Assert::IsTrue(callsTable.at("Moon").size() == 0);

		Assert::IsTrue(callsTable.at("Sun").size() == 0);
	}
};
