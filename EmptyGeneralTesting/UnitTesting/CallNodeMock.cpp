#include "stdafx.h"
#include "CallNodeMock.h"

CallNodeMock::CallNodeMock(int lineNumber) : StatementNode(lineNumber, new RangeNumber(0, 0)) {
}

CallNodeMock::~CallNodeMock() {
}

void CallNodeMock::addChild(Node* child) {
	//do nothing
}
