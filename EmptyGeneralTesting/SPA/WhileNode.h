#pragma once
#include "StatementNode.h"

class WhileNode: public StatementNode {
public:
	WhileNode();
	~WhileNode() override;

	// pozwala tylko na 2 childy: VariableNode i StmLstNode
	void addChild(Node* child) override;
	void validate() override;
};
