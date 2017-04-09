#pragma once
#include "StatementNode.h"

class IfNode: public StatementNode {

public:
	IfNode();
	~IfNode() override;

	// pozwala tylko na 3 childy: VariableNode, StmLstNode i StmLstNode
	void addChild(Node* child) override;
	void validate() override;
};
