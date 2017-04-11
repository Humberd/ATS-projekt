#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/StatementListNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

//TEST_CLASS(StatementListNodeTest) {
//	TEST_METHOD(StatementListNode_setLineNumber_getLineNumber) {
//		auto statementListNode = new StatementListNode(1);
//
//		Assert::IsTrue(1 == statementListNode->getLineNumber());
//
//		statementListNode->setLineNumber(5);
//
//		Assert::IsTrue(5 == statementListNode->getLineNumber());
//
//		delete statementListNode;
//	}
//
//	TEST_METHOD(StatementListNode_addChild_InvalidType) {
//		auto statementListNode = new StatementListNode(1);
//
//		auto pointer = [statementListNode] {
//			statementListNode->addChild(statementListNode);
//		};
//
//		Assert::ExpectException<invalid_argument>(pointer);
//
//		Assert::IsTrue(0 == statementListNode->getChildren().size());
//
//		delete statementListNode;
//	}
//
//	TEST_METHOD(StatementListNode_addChild_ValidType) {
//		
//	}
//
//	TEST_METHOD(StatementListNode_validate_0_children) {
//		
//	}
//
//	TEST_METHOD(StatementListNode_validate_1_child) {
//		
//	}
//};