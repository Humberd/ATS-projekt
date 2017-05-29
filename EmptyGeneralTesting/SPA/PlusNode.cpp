#include "PlusNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"

PlusNode::PlusNode(int sourceLineNumber) : ExpressionNode(sourceLineNumber, new RangeNumber(2, 2)) {
}

PlusNode::~PlusNode() {
}

void PlusNode::addChild(Node* child) {
	if (dynamic_cast<ExpressionNode*>(child) == nullptr) {
		throw invalid_argument("PlusNode accepts only ExpressionNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->_addChild(child);
}
