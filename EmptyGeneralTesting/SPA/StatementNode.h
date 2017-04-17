#pragma once
#include "Node.h"

class StatementNode: public Node {
protected:
	explicit StatementNode(int lineNumber, RangeNumber* rangeOfRequiredChildNodes);

public:
	virtual ~StatementNode();
};
