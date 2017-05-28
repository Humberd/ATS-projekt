#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/Spa.h"
#include "../SPA/FlowPathGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(NodeFlowPathTest) {
	Node* rootNode = Spa::generateAstFromFile("../IntegrationTesting/FlowPath.txt");
	SpaDataContainer* spaDataContainer = Spa::generateHelperTables(rootNode);

	TEST_METHOD(Test_1) {
		FlowPathGenerator::generateFlowPath(spaDataContainer);
	}
};