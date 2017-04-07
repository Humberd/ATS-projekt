#pragma once
#include "ExpressionNode.h"

class TimesNode: public ExpressionNode {
public:
	TimesNode();
	~TimesNode();

	// pozwala na 2 childy: ExpressionNode i ExpressionNode
	void addChild(Node* child) override;
	void validate() override;
};
