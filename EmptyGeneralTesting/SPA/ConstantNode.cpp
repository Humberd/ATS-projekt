#include "ConstantNode.h"
#include "ValidateException.h"
#include "InvalidArgumentException.h"

ConstantNode::ConstantNode(int lineNumber, int value) :Node(lineNumber, new RangeNumber(0, 0)) {
	this->value = value;
}

ConstantNode::~ConstantNode() {
}

void ConstantNode::setValue(int value) {
	this->value = value;
}

int ConstantNode::getValue() const {
	return this->value;
}

void ConstantNode::addChild(Node* child) {
	throw InvalidArgumentException(this, "WhileNode accepts 0 Nodes as a child, but instead got: " + string(typeid(*child).name()));
}
