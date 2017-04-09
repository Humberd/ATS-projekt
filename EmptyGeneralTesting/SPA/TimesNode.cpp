#include "TimesNode.h"
#include "ValidateException.h"

TimesNode::TimesNode() {
}

TimesNode::~TimesNode() {
}

void TimesNode::addChild(Node* child) {
	if (dynamic_cast<ExpressionNode*>(child) == nullptr) {
		throw invalid_argument("TimesNode accepts only ExpressionNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->children.push_back(child);
}

void TimesNode::validate() {
	int size = this->getChildren().size();
	if (size != 2) {
		throw ValidateException("TimesNode requires 2 ExpressionNodes, but instead got: " + size);
	}
}
