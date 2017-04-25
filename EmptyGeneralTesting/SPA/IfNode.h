#pragma once
#include "StatementNode.h"

class IfNode: public StatementNode {

public:
	explicit IfNode(int sourceLineNumber, int programLineNumber);
	~IfNode() override;

	// pozwala tylko na 3 childy: VariableNode, StmLstNode i StmLstNode
	void addChild(Node* child) override;
};
