#include "stdafx.h"
#include "IfNodeMock.h"

IfNodeMock::IfNodeMock(int sourceLineNumber) : StatementNode(sourceLineNumber, new RangeNumber(0, 0)) {
}

IfNodeMock::~IfNodeMock() {
}

void IfNodeMock::addChild(Node* child) {
	//do nothing
}
