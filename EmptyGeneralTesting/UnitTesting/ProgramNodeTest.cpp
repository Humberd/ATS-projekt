#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/ProgramNode.h"
#include "../SPA/ProcedureNode.h"
#include "../SPA/ValidateException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

//TEST_CLASS(ProgramNodeTest) {
//	TEST_METHOD(ProgramNode_addChild_InvalidType) {
//		auto programNode = new ProgramNode;
//
//		auto pointer = [programNode] { 
//			programNode->addChild(programNode); 
//		};
//
//		Assert::ExpectException<invalid_argument>(pointer);
//
//		Assert::IsTrue(0 == programNode->getChildren().size());
//
//		delete programNode;
//	}
//	TEST_METHOD(ProgramNode_addChild_ValidType) {
//		auto programNode = new ProgramNode;
//		auto procedureNode = new ProcedureNode("my Procedure");
//
//		programNode->addChild(procedureNode);
//
//		Assert::IsTrue(1 == programNode->getChildren().size());
//
//		delete programNode;
//	}
//
//	TEST_METHOD(ProgramNode_validate_0_Children) {
//		auto programNode = new ProgramNode;
//
//		auto pointer = [programNode] {
//			programNode->validate();
//		};
//		
//		Assert::ExpectException<ValidateException>(pointer);
//
//		delete programNode;
//	}
//
//	TEST_METHOD(ProgramNode_validate_1_Child) {
//		auto programNode = new ProgramNode;
//		auto procedureNode = new ProcedureNode("foo procedure");
//		programNode->addChild(procedureNode);
//
//		programNode->validate();
//
//		delete programNode;
//	}
//};

