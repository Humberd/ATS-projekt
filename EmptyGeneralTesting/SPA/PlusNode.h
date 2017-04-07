#pragma once
#include "ExpressionNode.h"

class PlusNode : public ExpressionNode {
public:
	PlusNode();
	~PlusNode();

	// pozwala na 2 childy: ExpressionNode i ExpressionNode
	void addChild(Node* child) override;
	void validate() override;
};
