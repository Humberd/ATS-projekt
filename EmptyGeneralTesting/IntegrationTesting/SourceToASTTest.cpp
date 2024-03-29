#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/Spa.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(SourceToASTTest) {
	TEST_METHOD(SourceToAST_AssignmentSource) {
		try {
			Node* rootNode = Spa::generateAstFromFile("../IntegrationTesting/autotest-1-source.txt");
			rootNode->prettyPrint();
		} catch (exception& e) {
			Logger::WriteMessage(e.what());
		}
	}
};
