#pragma once
#include "ExpressionNode.h"

class MinusNode: public ExpressionNode {
public: 
	MinusNode();
	~MinusNode();

	// pozwala na 2 childy: ExpressionNode i ExpressionNode
	void addChild(Node* child) override;
	void validate() override;
};
