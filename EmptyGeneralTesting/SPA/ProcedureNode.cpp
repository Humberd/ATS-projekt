#include "ProcedureNode.h"
#include "StatementListNode.h"
#include "ValidateException.h"
#include "InvalidArgumentException.h"


ProcedureNode::ProcedureNode(int lineNumber, string name) : Node(lineNumber, new RangeNumber(1, 1)) {
	setName(name);
}

ProcedureNode::~ProcedureNode() {
}

void ProcedureNode::setName(string name) {
	this->name = name;
}

string ProcedureNode::getName() const {
	return this->name;
}

void ProcedureNode::addChild(Node* child) {
	if (dynamic_cast<StatementListNode*>(child) == nullptr) {
		throw InvalidArgumentException(this, "ProcedureNode accepts only StatementListNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->_addChild(child);
}
