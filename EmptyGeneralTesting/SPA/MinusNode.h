#pragma once
#include "ExpressionNode.h"

class MinusNode: public ExpressionNode {
public: 
	explicit MinusNode(int lineNumber);
	~MinusNode() override;

	// pozwala na 2 childy: ExpressionNode i ExpressionNode
	void addChild(Node* child) override;
};
