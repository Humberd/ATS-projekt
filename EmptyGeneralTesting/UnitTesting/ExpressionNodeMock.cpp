#include "stdafx.h"
#include "ExpressionNodeMock.h"

ExpressionNodeMock::ExpressionNodeMock(int sourceLineNumber,
                                       int programLineNumber): ExpressionNode(sourceLineNumber, programLineNumber, new RangeNumber(0, 0)) {
}

ExpressionNodeMock::~ExpressionNodeMock() {
}

void ExpressionNodeMock::addChild(Node* child) {
	//do nothing
}
