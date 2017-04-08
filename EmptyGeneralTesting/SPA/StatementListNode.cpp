#include "StatementListNode.h"

StatementListNode::StatementListNode(int lineNumber) : lineNumber(lineNumber) {
}

StatementListNode::~StatementListNode() {
}

void StatementListNode::setLineNumber(int lineNumber) {
	this->lineNumber = lineNumber;
}


int StatementListNode::getLineNumber() {
	return this->lineNumber;
}

void StatementListNode::addChild(Node* child) {

}

void StatementListNode::validate() {

}

