#include "CallNode.h"
#include <vcruntime_typeinfo.h>
#include "InvalidArgumentException.h"

CallNode::CallNode(int lineNumber, string procedureName) :StatementNode(lineNumber, new RangeNumber(0, 0)) {
	this->procedureName = procedureName;
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
	throw InvalidArgumentException(this, "CallNode accepts 0 Nodes as a child, but instead got: " + string(typeid(*child).name()));
}
