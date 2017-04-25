#pragma once
#include "Node.h"

class ExpressionNode: public Node {
protected:
	explicit ExpressionNode(int sourceLineNumber, int programLineNumber, RangeNumber* rangeOfRequiredChildNodes);

public:
	virtual ~ExpressionNode();
};
