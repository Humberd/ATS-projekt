#pragma once
#include "../SPA/ExpressionNode.h"

class ExpressionNodeMock : public ExpressionNode {
public:
	explicit ExpressionNodeMock(int lineNumber);
	~ExpressionNodeMock();

	void addChild(Node* child) override;
};
