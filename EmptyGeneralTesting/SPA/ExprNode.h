#pragma once
#include "Node.h"

class ExprNode: public Node {
public:
	explicit ExprNode();
	virtual ~ExprNode() = 0;


	void addChild(Node* child) override;
};
