#pragma once
#include "Node.h"

class StatementNode: public Node {
protected:
	StatementNode();

public:
	virtual ~StatementNode() = 0;
};
