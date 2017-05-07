#pragma once
#include "Node.h"

class ExpressionNode: public Node {
protected:
	explicit ExpressionNode(int sourceLineNumber, RangeNumber* rangeOfRequiredChildNodes);

public:
	virtual ~ExpressionNode();
};
