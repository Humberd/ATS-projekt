#include "ConstantNode.h"
#include "ValidateException.h"

ConstantNode::ConstantNode(int value): value(value) {
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
	throw invalid_argument("WhileNode accepts 0 Nodes as a child, but instead got: " + string(typeid(*child).name()));
}

void ConstantNode::validate() {
	int size = this->getChildren().size();
	if (size != 0) {
		throw ValidateException("ConstantNode requires 0 Nodes, but instead got: " + size);
	}
}
