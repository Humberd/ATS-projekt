#include "stdafx.h"
#include "StatementListNodeMock.h"

StatementListNodeMock::StatementListNodeMock(int lineNumber) : Node(lineNumber, new RangeNumber(0, 0)) {
}

StatementListNodeMock::~StatementListNodeMock() {
}

void StatementListNodeMock::addChild(Node* child) {
	//do nothing
}
