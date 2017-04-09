#include "ReferenceNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"
#include "VariableNode.h"
#include "ConstantNode.h"
#include "InvalidArgumentException.h"

ReferenceNode::ReferenceNode(int lineNumber) : ExpressionNode(lineNumber, new RangeNumber(1, 1)) {
}

ReferenceNode::~ReferenceNode() {
}

void ReferenceNode::addChild(Node* child) {
	if (dynamic_cast<VariableNode*>(child) == nullptr
		&& dynamic_cast<ConstantNode*>(child) == nullptr) {
		throw InvalidArgumentException(this, "ReferenceNode accepts 1 VariableNode or ConstantNode as a child, but instea" + string(typeid(*child).name()));
	}

	this->_addChild(child);
}
