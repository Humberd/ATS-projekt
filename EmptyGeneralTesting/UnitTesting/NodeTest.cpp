#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/Node.h"
#include <memory>
#include "../SPA/ValidateException.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

class MockNode : public Node {

public:
	explicit MockNode(int sourceLineNumber,
	                  RangeNumber* rangeOfRequiredChildNodes) : Node(sourceLineNumber, rangeOfRequiredChildNodes) {
	}

	~MockNode() override {
	}

	void addChild(Node* child) override {
		this->_addChild(child);
	}
};

TEST_CLASS(NodeTest) {
	TEST_METHOD(Node_initialize_noChildren_noParent) {
		auto mockNode = new MockNode(2, new RangeNumber(1, 3));

		Assert::IsTrue(0 == mockNode->getChildren().size());
		Assert::IsNull(mockNode->getParent());
		Assert::IsTrue(2 == mockNode->getSourceLineNumber());

		delete mockNode;
	}

	TEST_METHOD(Node_getChildren_add2Children) {
		auto mockNode = new MockNode(1, new RangeNumber(2, 2));
		auto child1 = new MockNode(2, new RangeNumber(0, 0));
		auto child2 = new MockNode(3, new RangeNumber(0, 0));

		mockNode->addChild(child1);
		mockNode->addChild(child2);

		/*Is size == 2*/
		Assert::IsTrue(2 == mockNode->getChildren().size());
		Assert::IsTrue(mockNode == child1->getParent());
		Assert::IsTrue(mockNode == child2->getParent());

		/*Can get child at index*/
		Assert::IsTrue(child1 == mockNode->getChild(0));
		Assert::IsTrue(child2 == mockNode->getChild(1));

		auto pointer = [mockNode] {
			mockNode->getChild(2);
		};

		Assert::ExpectException<exception>(pointer);

		delete mockNode , child1 , child2;
	}

	TEST_METHOD(Node_getParent_setParent) {
		auto mockNode = new MockNode(2, new RangeNumber(0, 0));
		auto parentNode = new MockNode(1, new RangeNumber(1, 1));

		Assert::IsNull(mockNode->getParent());

		mockNode->setParent(parentNode);

		Assert::IsNotNull(mockNode->getParent());

		delete mockNode , parentNode;
	}

	TEST_METHOD(Node_validate_Valid) {
		auto parentNode = new MockNode(1, new RangeNumber(1, 1));
		auto childNode = new MockNode(2, new RangeNumber(0, 0));

		parentNode->addChild(childNode);

		parentNode->validate();

		delete parentNode , childNode;
	}

	TEST_METHOD(Node_validate_InvalidSelf) {
		auto parentNode = new MockNode(1, new RangeNumber(1, 1));

		auto pointer = [parentNode] {
			parentNode->validate();
		};

		Assert::ExpectException<ValidateException>(pointer);

		delete parentNode;
	}

	TEST_METHOD(Node_validate_InvalidChild) {
		auto parentNode = new MockNode(1, new RangeNumber(1, 1));
		auto childNode = new MockNode(2, new RangeNumber(1, 1));

		parentNode->addChild(childNode);

		auto pointer = [parentNode] {
			parentNode->validate();
		};

		Assert::ExpectException<ValidateException>(pointer);

		delete parentNode , childNode;
	}

	TEST_METHOD(Node_validate_LoopCatchSelf) {
		auto parentNode = new MockNode(1, new RangeNumber(1, 1));

		parentNode->addChild(parentNode);

		auto pointer = [parentNode] {
			parentNode->validate();
		};

		Assert::ExpectException<ValidateException>(pointer);

		delete parentNode;
	}

	TEST_METHOD(Node_validate_LoopCatchChild) {
		auto parentNode = new MockNode(1, new RangeNumber(1, 1));
		auto childNode = new MockNode(2, new RangeNumber(1, 1));

		parentNode->addChild(childNode);
		childNode->addChild(parentNode);

		auto pointer = [parentNode] {
			parentNode->validate();
		};

		Assert::ExpectException<ValidateException>(pointer);

		delete parentNode , childNode;
	}
};
