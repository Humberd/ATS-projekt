#pragma once
#include "ExpressionNode.h"

class ReferenceNode: public ExpressionNode {
private: 
	int value;

public:
	explicit ReferenceNode(int value);
	~ReferenceNode() override;

	void setValue(int value);
	int getValue() const;

	// pozwala na 0 childow
	void addChild(Node* child) override;
	void validate() override;
};
