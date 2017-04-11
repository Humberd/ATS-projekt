#pragma once
#include "ExpressionNode.h"

class PlusNode : public ExpressionNode {
public:
	explicit PlusNode(int lineNumber);
	~PlusNode() override;

	// pozwala na 2 childy: ExpressionNode i ExpressionNode
	void addChild(Node* child) override;
};
