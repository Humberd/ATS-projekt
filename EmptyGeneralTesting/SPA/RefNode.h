#pragma once
#include "ExprNode.h"

class RefNode: ExprNode {
private: 
	int value;

public:
	explicit RefNode();
	~RefNode();

	void setValue(int value);
	int getValue();

	void addChild(Node* child) override;
};
