#include "WhileNode.h"
#include "VariableNode.h"
#include "StatementListNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"
#include "InvalidArgumentException.h"

WhileNode::WhileNode(int lineNumber) : StatementNode(lineNumber, new RangeNumber(2, 2)) {
}

WhileNode::~WhileNode() {
}

void WhileNode::addChild(Node* child) {
	if (dynamic_cast<VariableNode*>(child) == nullptr
		&& dynamic_cast<StatementListNode*>(child) == nullptr) {
		throw InvalidArgumentException(this, "WhileNode accepts only VariableNode and StatementListNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->_addChild(child);
}
