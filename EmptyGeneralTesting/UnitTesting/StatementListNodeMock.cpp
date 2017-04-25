#include "stdafx.h"
#include "StatementListNodeMock.h"

StatementListNodeMock::StatementListNodeMock(int sourceLineNumber,
                                             int programLineNumber) : StatementListNode(sourceLineNumber, programLineNumber) {
}

StatementListNodeMock::~StatementListNodeMock() {
}

void StatementListNodeMock::addChild(Node* child) {
	//do nothing
}
