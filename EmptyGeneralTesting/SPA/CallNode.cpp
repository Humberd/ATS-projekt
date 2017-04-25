#include "CallNode.h"
#include <vcruntime_typeinfo.h>
#include "InvalidArgumentException.h"

CallNode::CallNode(int sourceLineNumber,
                   int programLineNumber,
                   string procedureName) : StatementNode(sourceLineNumber, programLineNumber, new RangeNumber(0, 0)) {
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


string CallNode::toString() const {
	return Node::toString() + " - procName: " + procedureName;
}
