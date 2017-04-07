#pragma once
#include "Node.h"

class ExprNode: public Node {
protected:
	ExprNode();

public:
	virtual ~ExprNode() = 0;
};
