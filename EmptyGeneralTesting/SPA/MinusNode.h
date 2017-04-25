#pragma once
#include "ExpressionNode.h"

class MinusNode: public ExpressionNode {
public: 
	explicit MinusNode(int sourceLineNumber, int programLineNumber);
	~MinusNode() override;

	// pozwala na 2 childy: ExpressionNode i ExpressionNode
	void addChild(Node* child) override;
};
