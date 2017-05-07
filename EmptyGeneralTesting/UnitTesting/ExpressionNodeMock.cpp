#include "stdafx.h"
#include "ExpressionNodeMock.h"

ExpressionNodeMock::ExpressionNodeMock(int sourceLineNumber): ExpressionNode(sourceLineNumber, new RangeNumber(0, 0)) {
}

ExpressionNodeMock::~ExpressionNodeMock() {
}

void ExpressionNodeMock::addChild(Node* child) {
	//do nothing
}
