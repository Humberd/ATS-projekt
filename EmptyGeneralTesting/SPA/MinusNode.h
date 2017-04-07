#pragma once
#include "ExprNode.h"

class MinusNode: public ExprNode {
public: 
	MinusNode();
	~MinusNode();

	void addChild(Node* child) override;
	void validate() override;
};
