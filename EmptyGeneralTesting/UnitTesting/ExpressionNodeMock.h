#pragma once
#include "../SPA/ExpressionNode.h"

class ExpressionNodeMock : public ExpressionNode {
public:
	explicit ExpressionNodeMock(int sourceLineNumber);
	~ExpressionNodeMock();

	void addChild(Node* child) override;
};
