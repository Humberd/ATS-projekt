#include "WhileNode.h"
#include "VariableNode.h"
#include "StatementListNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"

WhileNode::WhileNode() {
}

WhileNode::~WhileNode() {
}

void WhileNode::addChild(Node* child) {
	if (dynamic_cast<VariableNode*>(child) == nullptr
		&& dynamic_cast<StatementListNode*>(child) == nullptr) {
		throw invalid_argument("WhileNode accepts only VariableNode and StatementListNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->children.push_back(child);
}

void WhileNode::validate() {
	int size = this->getChildren().size();
	if (size != 2) {
		throw ValidateException("WhileNode requires 2 Nodes: VariableNode and StatementListNode, but instead got: " + size);
	}
}


