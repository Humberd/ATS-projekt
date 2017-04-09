#include "CallNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"

CallNode::CallNode(string procedureName): procedureName(procedureName) {
}
CallNode::~CallNode() {
}

string CallNode::getProcedureName() const {
	return procedureName;
}

void CallNode::setProcedureName(string procedureName) {
	this->procedureName = procedureName;
}

void CallNode::addChild(Node* child) {
	throw invalid_argument("CallNode accepts 0 Nodes as a child, but instead got: " + string(typeid(*child).name()));
}

void CallNode::validate() {
	int size = this->getChildren().size();
	if(size != 0) {
		throw ValidateException("CallNode requires 0 Nodes, but instead got: " + size);
	}
}
