#pragma once
#include "Node.h"

class StatementNode: public Node {
protected:
	explicit StatementNode(int sourceLineNumber, RangeNumber* rangeOfRequiredChildNodes);

public:
	virtual ~StatementNode();
};
