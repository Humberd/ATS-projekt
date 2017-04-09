#include "StatementListNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"
#include "StatementNode.h"

StatementListNode::StatementListNode(int lineNumber) : lineNumber(lineNumber) {
}

StatementListNode::~StatementListNode() {
}

void StatementListNode::setLineNumber(int lineNumber) {
	this->lineNumber = lineNumber;
}


int StatementListNode::getLineNumber() const {
	return this->lineNumber;
}

void StatementListNode::addChild(Node* child) {
	if (dynamic_cast<StatementNode*>(child) == nullptr) {
		throw invalid_argument("StatementListNode accepts only StatementNode as a child, but instead got: " + string(typeid(*child).name()));
	}

	this->children.push_back(child);
}

void StatementListNode::validate() {
	int size = this->getChildren().size();
	if (size == 0) {
		throw ValidateException("StatementListNode requires 1+ StatementNodes, but instead got: " + size);
	}
}

