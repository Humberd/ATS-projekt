#pragma once
#include "ExpressionNode.h"

class ReferenceNode: public ExpressionNode {
protected:
	explicit ReferenceNode(int sourceLineNumber, int programLineNumber);

public:
	virtual ~ReferenceNode();
};
