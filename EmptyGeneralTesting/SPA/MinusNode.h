#pragma once
#include "ExprNode.h"

class MinusNode: ExprNode {
public: 
	explicit MinusNode();
	~MinusNode();

	void addChild(Node* child) override;
};
