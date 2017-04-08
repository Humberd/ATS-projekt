#include "ProgramNode.h"
#include "ProcedureNode.h"
#include <memory>

ProgramNode::ProgramNode() {
}
ProgramNode::~ProgramNode() {
}

void ProgramNode::addChild(Node* child) {
}

void ProgramNode::validate() {
	int size = this->getChildren().size();
	if (size == 0) {
		throw "Program node requires 1+ ProcedureNodes, but instead got: " + size;
	}
}
