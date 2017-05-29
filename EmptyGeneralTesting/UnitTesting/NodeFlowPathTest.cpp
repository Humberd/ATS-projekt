#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/Spa.h"
#include "../SPA/FlowPathGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(NodeFlowPathTest) {
	TEST_METHOD(FlowPathGenerator_test_FlowPath_txt) {
		Node* rootNode = Spa::generateAstFromFile("../IntegrationTesting/FlowPath.txt");
		SpaDataContainer* spaDataContainer = Spa::generateHelperTables(rootNode);
		FlowPathGenerator::generateFlowPath(spaDataContainer);

		map<int, NodeFlowWrapper*> flowWrappersTable = spaDataContainer->flowWrappersTable;

		Assert::IsTrue(flowWrappersTable.size() == 8);
		Assert::IsTrue(flowWrappersTable.at(1)->getPathsIntoNode().size() == 1);
		Assert::IsTrue(flowWrappersTable.at(1)->getPathsOutOfNode().size() == 1);

		/*WhileNode*/
		Assert::IsTrue(flowWrappersTable.at(2)->getPathsIntoNode().size() == 2);
		Assert::IsTrue(flowWrappersTable.at(2)->getPathsOutOfNode().size() == 2);

		Assert::IsTrue(flowWrappersTable.at(3)->getPathsIntoNode().size() == 1);
		Assert::IsTrue(flowWrappersTable.at(3)->getPathsOutOfNode().size() == 1);

		Assert::IsTrue(flowWrappersTable.at(4)->getPathsIntoNode().size() == 1);
		Assert::IsTrue(flowWrappersTable.at(4)->getPathsOutOfNode().size() == 1);

		/*IfNode*/
		Assert::IsTrue(flowWrappersTable.at(5)->getPathsIntoNode().size() == 1);
		Assert::IsTrue(flowWrappersTable.at(5)->getPathsOutOfNode().size() == 2);

		Assert::IsTrue(flowWrappersTable.at(6)->getPathsIntoNode().size() == 1);
		Assert::IsTrue(flowWrappersTable.at(6)->getPathsOutOfNode().size() == 1);

		Assert::IsTrue(flowWrappersTable.at(7)->getPathsIntoNode().size() == 1);
		Assert::IsTrue(flowWrappersTable.at(7)->getPathsOutOfNode().size() == 1);

		Assert::IsTrue(flowWrappersTable.at(8)->getPathsIntoNode().size() == 2);
		Assert::IsTrue(flowWrappersTable.at(8)->getPathsOutOfNode().size() == 0);

		delete rootNode, spaDataContainer;

		for (auto entrySet : flowWrappersTable) {
			delete entrySet.second;
		}
	}

	TEST_METHOD(FlowPathGenerator_test_NestedFlowPath_txt) {
		Node* rootNode = Spa::generateAstFromFile("../IntegrationTesting/NestedFlowPath.txt");
		SpaDataContainer* spaDataContainer = Spa::generateHelperTables(rootNode);
		FlowPathGenerator::generateFlowPath(spaDataContainer);

		map<int, NodeFlowWrapper*> flowWrappersTable = spaDataContainer->flowWrappersTable;

		Assert::IsTrue(flowWrappersTable.size() == 4);
		/*WhileNode*/
		Assert::IsTrue(flowWrappersTable.at(1)->getPathsIntoNode().size() == 3);
		Assert::IsTrue(flowWrappersTable.at(1)->getPathsOutOfNode().size() == 1);

		/*IfNode*/
		Assert::IsTrue(flowWrappersTable.at(2)->getPathsIntoNode().size() == 1);
		Assert::IsTrue(flowWrappersTable.at(2)->getPathsOutOfNode().size() == 2);

		Assert::IsTrue(flowWrappersTable.at(3)->getPathsIntoNode().size() == 1);
		Assert::IsTrue(flowWrappersTable.at(3)->getPathsOutOfNode().size() == 1);

		Assert::IsTrue(flowWrappersTable.at(4)->getPathsIntoNode().size() == 1);
		Assert::IsTrue(flowWrappersTable.at(4)->getPathsOutOfNode().size() == 1);

		delete rootNode, spaDataContainer;

		for (auto entrySet : flowWrappersTable) {
			delete entrySet.second;
		}
	}
};