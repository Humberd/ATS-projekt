#include "stdafx.h"
#include "WhileNodeMock.h"

WhileNodeMock::WhileNodeMock(int sourceLineNumber,
                             int programLineNumber) : StatementNode(sourceLineNumber, programLineNumber, new RangeNumber(0, 0)) {
}

WhileNodeMock::~WhileNodeMock() {
}

void WhileNodeMock::addChild(Node* child) {
	//do nothing
}
