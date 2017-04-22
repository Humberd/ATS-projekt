#pragma once
#include "stdafx.h"
#include "../SPA/ExpressionNode.h"

class ExpressionNodeMock : public ExpressionNode {
public:
	ExpressionNodeMock(int lineNumber);
	~ExpressionNodeMock();

	void addChild(Node* child) override;
};
