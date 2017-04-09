#include "AssignNode.h"
#include "VariableNode.h"
#include "ExpressionNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"
#include "InvalidArgumentException.h"


AssignNode::AssignNode(int lineNumber) : StatementNode(lineNumber, new RangeNumber(2, 2)) {
}

AssignNode::~AssignNode() {
}

void AssignNode::addChild(Node* child) {
	if (dynamic_cast<VariableNode*>(child) == nullptr
		&& dynamic_cast<ExpressionNode*>(child) == nullptr) {
		throw InvalidArgumentException(this, "AssignNode accepts only VariableNode or ExpressionNode  as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->_addChild(child);
}
