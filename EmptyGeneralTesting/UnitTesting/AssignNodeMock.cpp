#include "stdafx.h"
#include "AssignNodeMock.h"

AssignNodeMock::AssignNodeMock(int sourceLineNumber,
                               int programLineNumber) : StatementNode(sourceLineNumber, programLineNumber, new RangeNumber(0, 0)) {
}

AssignNodeMock::~AssignNodeMock() {
}

void AssignNodeMock::addChild(Node* child) {
	//do nothing
}
