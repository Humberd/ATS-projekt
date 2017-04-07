#pragma once
#include "ExprNode.h"

class RefNode: public ExprNode {
private: 
	int value;

public:
	explicit RefNode(int value);
	~RefNode();

	void setValue(int value);
	int getValue();

	void addChild(Node* child) override;
	void validate() override;
};
