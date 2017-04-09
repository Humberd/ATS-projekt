#include "MinusNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"

MinusNode::MinusNode() {
}

MinusNode::~MinusNode() {
}

void MinusNode::addChild(Node* child) {
	if (dynamic_cast<ExpressionNode*>(child) == nullptr) {
		throw invalid_argument("MinusNode accepts only ExpressionNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->children.push_back(child);
}

void MinusNode::validate() {
	int size = this->getChildren().size();
	if (size != 2) {
		throw ValidateException("MinusNode requires 2 ExpressionNodes, but instead got: " + size);
	}
}
