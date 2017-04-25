#include "stdafx.h"
#include "CallNodeMock.h"

CallNodeMock::CallNodeMock(int sourceLineNumber,
                           int programLineNumber) : StatementNode(sourceLineNumber, programLineNumber, new RangeNumber(0, 0)) {
}

CallNodeMock::~CallNodeMock() {
}

void CallNodeMock::addChild(Node* child) {
	//do nothing
}
