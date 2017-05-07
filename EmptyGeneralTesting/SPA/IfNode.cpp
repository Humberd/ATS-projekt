#include "IfNode.h"
#include "StatementListNode.h"
#include "VariableNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"
#include "InvalidArgumentException.h"

IfNode::IfNode(int sourceLineNumber) : StatementNode(sourceLineNumber, new RangeNumber(3, 3)) {
}

IfNode::~IfNode() {
}

void IfNode::addChild(Node* child) {
	if (dynamic_cast<VariableNode*>(child) == nullptr
		&& dynamic_cast<StatementListNode*>(child) == nullptr) {
		throw InvalidArgumentException(this, "IfNode accepts only VariableNode and StatementListNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->_addChild(child);
}
