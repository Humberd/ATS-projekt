#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/Spa.h"
#include "../SPA/SpaDataContainer.h"
#include "../SPA/TreeAnalyzer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(TreeAnalyzerTest) {
	TEST_METHOD(TreeAnalyzer_analyzeParentsTable) {
		Node* rootNode = Spa::generateAstFromFile("../IntegrationTesting/Source2.txt");

		SpaDataContainer* dataContainer = TreeAnalyzer::analyzeTree(rootNode);

	}
};