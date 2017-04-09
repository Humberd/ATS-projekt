#include "IfNode.h"
#include "StatementListNode.h"
#include "VariableNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"

IfNode::IfNode() {
}

IfNode::~IfNode() {
}

void IfNode::addChild(Node* child) {
	if (dynamic_cast<VariableNode*>(child) == nullptr
		&& dynamic_cast<StatementListNode*>(child) == nullptr) {
		throw invalid_argument("IfNode accepts only VariableNode and StatementListNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->children.push_back(child);
}

void IfNode::validate() {
	int size = this->getChildren().size();
	if (size != 3) {
		throw ValidateException("IfNode requires 3 Nodes: VariableNode and StatementListNode, but instead got: " + size);
	}
}
