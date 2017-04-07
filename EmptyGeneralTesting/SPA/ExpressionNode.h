#pragma once
#include "Node.h"

class ExpressionNode: public Node {
protected:
	ExpressionNode();

public:
	virtual ~ExpressionNode() = 0;
};
