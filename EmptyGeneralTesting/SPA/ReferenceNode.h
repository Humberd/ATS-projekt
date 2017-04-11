#pragma once
#include "ExpressionNode.h"

class ReferenceNode: public ExpressionNode {
public:
	explicit ReferenceNode(int lineNumber);
	~ReferenceNode() override;

	// pozwala na 1 child
	void addChild(Node* child) override;
};
