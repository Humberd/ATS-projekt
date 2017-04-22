#include "stdafx.h"
#include "ExpressionNodeMock.h"

ExpressionNodeMock::ExpressionNodeMock(int lineNumber): ExpressionNode(lineNumber, new RangeNumber(0, 0)) {
}

ExpressionNodeMock::~ExpressionNodeMock() {
}

void ExpressionNodeMock::addChild(Node* child) {
	//do nothing
}
