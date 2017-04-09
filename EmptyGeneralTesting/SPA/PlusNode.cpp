#include "PlusNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"

PlusNode::PlusNode() {
}

PlusNode::~PlusNode() {
}

void PlusNode::addChild(Node* child) {
	if (dynamic_cast<ExpressionNode*>(child) == nullptr) {
		throw invalid_argument("PlusNode accepts only ExpressionNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->children.push_back(child);
}

void PlusNode::validate() {
	int size = this->getChildren().size();
	if (size != 2) {
		throw ValidateException("PlusNode requires 2 ExpressionNodes, but instead got: " + size);
	}
}
