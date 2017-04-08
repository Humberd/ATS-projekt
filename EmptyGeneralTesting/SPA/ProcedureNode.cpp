#include "ProcedureNode.h"
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
}

void ProcedureNode::validate() {
	int size = this->getChildren().size();
	if (size != 1) {
		throw "ProcedureNode requires only 1 StatementListNode, but instead got: " + size;
	}
}
