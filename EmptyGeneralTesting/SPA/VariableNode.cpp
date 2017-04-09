#include "VariableNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"
#include "InvalidArgumentException.h"

VariableNode::VariableNode(int lineNumber, string name) : Node(lineNumber, new RangeNumber(0, 0)) {
	this->name = name;
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
	throw InvalidArgumentException(this, "VariableNode accepts 0 Nodes as a child, but instead got: " + string(typeid(*child).name()));
}