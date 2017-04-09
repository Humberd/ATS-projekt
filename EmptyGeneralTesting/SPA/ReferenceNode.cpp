#include "ReferenceNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"

ReferenceNode::ReferenceNode(int value) :value(value) {
}

ReferenceNode::~ReferenceNode() {
}

void ReferenceNode::setValue(int value) {
	this->value = value;
}

int ReferenceNode::getValue() const {
	return this->value;
}

void ReferenceNode::addChild(Node* child) {
	throw invalid_argument("ReferenceNode accepts 0 Nodes as a child, but instead got: " + string(typeid(*child).name()));
}

void ReferenceNode::validate() {
	int size = this->getChildren().size();
	if (size != 0) {
		throw ValidateException("ReferenceNode requires 0 Nodes, but instead got: " + size);
	}
}
