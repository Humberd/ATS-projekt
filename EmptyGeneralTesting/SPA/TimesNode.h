#pragma once
#include "ExpressionNode.h"

class TimesNode: public ExpressionNode {
public:
	explicit TimesNode(int sourceLineNumber, int programLineNumber);
	~TimesNode() override;

	// pozwala na 2 childy: ExpressionNode i ExpressionNode
	void addChild(Node* child) override;
};
