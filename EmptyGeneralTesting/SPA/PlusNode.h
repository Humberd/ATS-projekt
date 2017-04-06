#pragma once
#include "ExprNode.h"

class PlusNode: ExprNode {
public: 
	explicit PlusNode();
	~PlusNode();


	void addChild(Node* child) override;
};
