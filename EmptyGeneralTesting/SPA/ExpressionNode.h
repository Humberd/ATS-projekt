#pragma once
#include "Node.h"

class ExpressionNode: public Node {
protected:
	explicit ExpressionNode(int lineNumber, RangeNumber* rangeOfRequiredChildNodes);

public:
	virtual ~ExpressionNode() = 0;
};
