#include "ProcedureNode.h"
#include "StatementListNode.h"
#include <memory>
#include "ValidateException.h"

ProcedureNode::ProcedureNode(string name): name(name) {
}

ProcedureNode::~ProcedureNode() {
}

void ProcedureNode::setName(string name) {
	this->name = name;
}

string ProcedureNode::getName() const{
	return this->name;
}

void ProcedureNode::addChild(Node* child) {
	if (dynamic_cast<StatementListNode*>(child) == nullptr) {
		throw invalid_argument("ProcedureNode accepts only StatementListNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->children.push_back(child);
}

void ProcedureNode::validate() {
	int size = this->getChildren().size();
	if (size != 1) {
		throw ValidateException("ProcedureNode requires only 1 StatementListNode, but instead got: " + size);
	}
}
