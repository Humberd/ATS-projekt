#pragma once
#include "ExpressionNode.h"

class ReferenceNode: public ExpressionNode {
protected:
	explicit ReferenceNode(int lineNumber);

public:
	virtual ~ReferenceNode();
};
