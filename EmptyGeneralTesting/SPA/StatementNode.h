#pragma once
#include "Node.h"

class StatementNode: public Node {
protected:
	explicit StatementNode(int sourceLineNumber, int programLineNumber, RangeNumber* rangeOfRequiredChildNodes);

public:
	virtual ~StatementNode();
};
