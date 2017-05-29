#include "StatementListNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"
#include "StatementNode.h"
#include "InvalidArgumentException.h"

StatementListNode::StatementListNode(int sourceLineNumber) : Node(sourceLineNumber, new RangeNumber(1, INT32_MAX)) {
}

StatementListNode::~StatementListNode() {
}

void StatementListNode::addChild(Node* child) {
	if (dynamic_cast<StatementNode*>(child) == nullptr) {
		throw InvalidArgumentException(this, "StatementListNode accepts only StatementNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->_addChild(child);
}
