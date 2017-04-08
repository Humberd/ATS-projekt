#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/ProgramNode.h"
#include "../SPA/ProcedureNode.h"
#include "../SPA/ValidateException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ProgramNodeTest) {
	TEST_METHOD(addChild_InvalidType) {
		ProgramNode* programNode = new ProgramNode;

		auto pointer = [programNode] { 
			programNode->addChild(programNode); 
		};

		Assert::ExpectException<invalid_argument>(pointer);

		Assert::IsTrue(0 == programNode->getChildren().size());

		delete programNode;
	}
	TEST_METHOD(addChild_ValidType) {
		ProgramNode* programNode = new ProgramNode;
		ProcedureNode* procedureNode = new ProcedureNode("my Procedure");

		programNode->addChild(procedureNode);

		Assert::IsTrue(1 == programNode->getChildren().size());

		delete programNode, procedureNode;
	}

	TEST_METHOD(validate_0_Children) {
		ProgramNode* programNode = new ProgramNode;

		auto pointer = [programNode] {
			programNode->validate();
		};
		
		Assert::ExpectException<ValidateException>(pointer);

		delete programNode;
	}

	TEST_METHOD(validate_1_Child) {
		ProgramNode* programNode = new ProgramNode;
		ProcedureNode* procedureNode = new ProcedureNode("foo procedure");
		programNode->addChild(procedureNode);

		programNode->validate();

		delete programNode, procedureNode;
	}
};

