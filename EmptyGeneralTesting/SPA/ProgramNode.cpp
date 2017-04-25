#include "ProgramNode.h"
#include "ProcedureNode.h"
#include "ValidateException.h"
#include "InvalidArgumentException.h"

ProgramNode::ProgramNode(int sourceLineNumber,
                         int programLineNumber): Node(sourceLineNumber, programLineNumber, new RangeNumber(1, INT32_MAX)) {
}

ProgramNode::~ProgramNode() {
}

void ProgramNode::addChild(Node* child) {
	if (dynamic_cast<ProcedureNode*>(child) == nullptr) {
		throw InvalidArgumentException(this, "ProgramNode accepts only ProcedureNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->_addChild(child);
}
