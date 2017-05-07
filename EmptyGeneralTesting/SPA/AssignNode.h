#pragma once
#include "StatementNode.h"

class AssignNode: public StatementNode {

public:
	explicit AssignNode(int sourceLineNumber);
	~AssignNode() override;

	// pozwala tylko na 2 childy: VariableNode i ExpressionNode
	void addChild(Node* child) override;
};
