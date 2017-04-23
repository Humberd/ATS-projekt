#include "stdafx.h"
#include "IfNodeMock.h"

IfNodeMock::IfNodeMock(int lineNumber) : StatementNode(lineNumber, new RangeNumber(0, 0)) {
}

IfNodeMock::~IfNodeMock() {
}

void IfNodeMock::addChild(Node* child) {
	//do nothing
}
