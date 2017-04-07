#pragma once
#include "ExprNode.h"

class PlusNode : public ExprNode {
public:
	PlusNode();
	~PlusNode();

	void addChild(Node* child) override;
	void validate() override;
};
