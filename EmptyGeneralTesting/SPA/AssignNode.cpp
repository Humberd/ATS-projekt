#include "AssignNode.h"
#include "VariableNode.h"
#include "ExpressionNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"

AssignNode::AssignNode() {
}
AssignNode::~AssignNode() {
}

void AssignNode::addChild(Node* child) {
	if(dynamic_cast<VariableNode*>(child) == nullptr
		&& dynamic_cast<ExpressionNode*>(child) == nullptr) {
		throw invalid_argument("AssignNode accepts only VariableNode or ExpressionNode  as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->children.push_back(child);
}

void AssignNode::validate() {
	int size = this->getChildren().size();
	if (size != 2) {
		throw ValidateException("AssignNode requires 2 Nodes: VariableNode and ExpressionNode, but instead got: " + size);
	}
}



