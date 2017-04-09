#include "VariableNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"

VariableNode::VariableNode(string name): name(name) {
}

VariableNode::~VariableNode() {
}

void VariableNode::setName(string name) {
	this->name = name;
}

string VariableNode::getName() const {
	return this->name;
}

void VariableNode::addChild(Node* child) {
	throw invalid_argument("VariableNode accepts 0 Nodes as a child, but instead got: " + string(typeid(*child).name()));
}

void VariableNode::validate() {
	int size = this->getChildren().size();
	if (size != 0) {
		throw ValidateException("VariableNode requires 0 Nodes, but instead got: " + size);
	}
}
