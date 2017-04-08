#include "ProgramNode.h"
#include "ProcedureNode.h"
#include <memory>
#include "ValidateException.h"

ProgramNode::ProgramNode() {
}
ProgramNode::~ProgramNode() {
}

void ProgramNode::addChild(Node* child) {
	if(dynamic_cast<ProcedureNode*>(child) == nullptr) {
		throw invalid_argument("ProgramNode accepts only ProcedureNode as a child, but instead got: " + string(typeid(child).name()));
	}

	this->children.push_back(child);
}

void ProgramNode::validate() {
	int size = this->getChildren().size();
	if (size == 0) {
		throw ValidateException("ProgramNode requires 1+ ProcedureNodes, but instead got: " + size);
	}
}
