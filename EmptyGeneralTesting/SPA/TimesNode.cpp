#include "TimesNode.h"
#include "ValidateException.h"

TimesNode::TimesNode(int sourceLineNumber) : ExpressionNode(sourceLineNumber, new RangeNumber(2, 2)) {
}

TimesNode::~TimesNode() {
}

void TimesNode::addChild(Node* child) {
	if (dynamic_cast<ExpressionNode*>(child) == nullptr) {
		throw invalid_argument("TimesNode accepts only ExpressionNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->_addChild(child);
}
