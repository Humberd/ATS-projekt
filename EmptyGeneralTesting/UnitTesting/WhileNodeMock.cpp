#include "stdafx.h"
#include "WhileNodeMock.h"

WhileNodeMock::WhileNodeMock(int lineNumber) : StatementNode(lineNumber, new RangeNumber(0, 0)) {
}

WhileNodeMock::~WhileNodeMock() {
}

void WhileNodeMock::addChild(Node* child) {
	//do nothing
}
