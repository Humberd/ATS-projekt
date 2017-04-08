#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/Node.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

class MockNode : public Node {

public:
	~MockNode() override {
	}

	void addChild(Node* child) override {
		this->children.push_back(child);
	}

	void validate() override {

	}
};

TEST_CLASS(NodeTest) {
	TEST_METHOD(getChildren_newEmpty) {
		auto mockNode = new MockNode;

		Assert::IsTrue(0 == mockNode->getChildren().size());

		delete mockNode;
	}

	TEST_METHOD(getChildren_add2Children) {
		auto mockNode = new MockNode;
		auto child1 = new MockNode;
		auto child2 = new MockNode;

		mockNode->addChild(child1);
		mockNode->addChild(child2);

		Assert::IsTrue(2 == mockNode->getChildren().size());

		delete mockNode, child1, child2;
	}

	TEST_METHOD(getParent_setParent) {
		auto mockNode = new MockNode;
		auto parentNode = new MockNode;

		Assert::IsNull(mockNode->getParent());

		mockNode->setParent(parentNode);

		Assert::IsNotNull(mockNode->getParent());

		delete mockNode, parentNode;
	}
};