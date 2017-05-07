#include "stdafx.h"
#include "StatementListNodeMock.h"

StatementListNodeMock::StatementListNodeMock(int sourceLineNumber) : StatementListNode(sourceLineNumber) {
}

StatementListNodeMock::~StatementListNodeMock() {
}

void StatementListNodeMock::addChild(Node* child) {
	//do nothing
}
