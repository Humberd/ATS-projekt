#include "stdafx.h"
#include "StatementListNodeMock.h"

StatementListNodeMock::StatementListNodeMock(int lineNumber) : StatementListNode(lineNumber) {
}

StatementListNodeMock::~StatementListNodeMock() {
}

void StatementListNodeMock::addChild(Node* child) {
	//do nothing
}
