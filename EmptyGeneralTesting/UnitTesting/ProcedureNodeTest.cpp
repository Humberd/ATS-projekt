#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/ProcedureNode.h"
#include "../SPA/StatementListNode.h"
#include "../SPA/ValidateException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ProcedureNodeTest) {
	TEST_METHOD(ProcedureNode_setName_getName) {
		auto procedureNode = new ProcedureNode("myProcName");

		Assert::IsTrue("myProcName" == procedureNode->getName());

		procedureNode->setName("newProcName");

		Assert::IsTrue("newProcName" == procedureNode->getName());

		delete procedureNode;
	}

	TEST_METHOD(ProcedureNode_addChild_InvalidType) {
		auto procedureNode = new ProcedureNode("myProcName");

		auto pointer = [procedureNode] {
			procedureNode->addChild(procedureNode);
		};

		Assert::ExpectException<invalid_argument>(pointer);

		Assert::IsTrue(0 == procedureNode->getChildren().size());

		delete procedureNode;
	}

	TEST_METHOD(ProcedureNode_addChild_ValidType) {
		auto procedureNode = new ProcedureNode("myProcName");
		auto statementListNode = new StatementListNode(1);

		procedureNode->addChild(statementListNode);

		Assert::IsTrue(1 == procedureNode->getChildren().size());

		delete procedureNode;
	}

	TEST_METHOD(ProcedureNode_validate_0_Children) {
		auto procedureNode = new ProcedureNode("myProcName");

		auto pointer = [procedureNode] {
			procedureNode->validate();
		};

		Assert::ExpectException<ValidateException>(pointer);

		delete procedureNode;
	}

	TEST_METHOD(ProcedureNode_validate_1_Child) {
		auto procedureNode = new ProcedureNode("myProcName");
		auto statementListNode = new StatementListNode(1);

		procedureNode->addChild(statementListNode);

		procedureNode->validate();

		delete procedureNode;
	}

	TEST_METHOD(ProcedureNode_validate_2_Children) {
		auto procedureNode = new ProcedureNode("myProcName");
		auto statementListNode1 = new StatementListNode(1);
		auto statementListNode2 = new StatementListNode(2);

		procedureNode->addChild(statementListNode1);
		procedureNode->addChild(statementListNode2);

		auto pointer = [procedureNode] {
			procedureNode->validate();
		};

		Assert::ExpectException<ValidateException>(pointer);

		delete procedureNode;
	}
};