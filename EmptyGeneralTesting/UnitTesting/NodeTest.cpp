#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/Node.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(FOO) {
	TEST_METHOD(DUPA) {
		
	}
};

//class MockNode : public Node {
//
//public:
//	MockNode(int lineNumber, RangeNumber* rangeOfRequiredChildNodes) : Node(lineNumber, rangeOfRequiredChildNodes) {
//	}
//
//	~MockNode() override {
//	}
//
//	void addChild(Node* child) override {
//		this->_addChild(child);
//	}
//
//	void validate() override {
//		Node::validate();
//	}
//};
//
//TEST_CLASS(NodeTest) {
//	TEST_METHOD(Node_initialize_noChildren_noParent) {
//		auto mockNode = new MockNode(1, new RangeNumber(1, 3));
//
//		Assert::IsTrue(0 == mockNode->getChildren().size());
//		Assert::IsNull(mockNode->getParent());
//		Assert::IsTrue(1 == mockNode->getLineNumber());
//
//		delete mockNode;
//	}
//
//	TEST_METHOD(Node_getChildren_add2Children) {
//		auto mockNode = new MockNode(1, new RangeNumber(2, 2));
//		auto child1 = new MockNode(2, new RangeNumber(0, 0));
//		auto child2 = new MockNode(3, new RangeNumber(0, 0));
//
//		mockNode->addChild(child1);
//		mockNode->addChild(child2);
//
//		Assert::IsTrue(2 == mockNode->getChildren().size());
//		Assert::IsTrue(mockNode == child1->getParent());
//		Assert::IsTrue(mockNode == child2->getParent());
//
//		delete mockNode, child1, child2;
//	}
//
//	TEST_METHOD(Node_getParent_setParent) {
//		auto mockNode = new MockNode(2, new RangeNumber(0, 0));
//		auto parentNode = new MockNode(1, new RangeNumber(1, 1));
//
//		Assert::IsNull(mockNode->getParent());
//
//		mockNode->setParent(parentNode);
//
//		Assert::IsNotNull(mockNode->getParent());
//
//		delete mockNode;
//	}
//};