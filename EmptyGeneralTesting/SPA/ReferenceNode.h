#pragma once
#include "ExpressionNode.h"

class ReferenceNode: public ExpressionNode {
private: 
	int value;

public:
	explicit ReferenceNode(int value);
	~ReferenceNode();

	void setValue(int value);
	int getValue();

	// pozwala na 0 childow
	void addChild(Node* child) override;
	void validate() override;
};
