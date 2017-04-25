#pragma once
#include "../SPA/ExpressionNode.h"

class ExpressionNodeMock : public ExpressionNode {
public:
	explicit ExpressionNodeMock(int sourceLineNumber, int programLineNumber);
	~ExpressionNodeMock();

	void addChild(Node* child) override;
};
