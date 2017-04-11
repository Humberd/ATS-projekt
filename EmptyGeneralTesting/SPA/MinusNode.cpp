#include "MinusNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"

MinusNode::MinusNode(int lineNumber): ExpressionNode(lineNumber, new RangeNumber(2,2)) {
}

MinusNode::~MinusNode() {
}

void MinusNode::addChild(Node* child) {
	if (dynamic_cast<ExpressionNode*>(child) == nullptr) {
		throw invalid_argument("MinusNode accepts only ExpressionNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->_addChild(child);
}
