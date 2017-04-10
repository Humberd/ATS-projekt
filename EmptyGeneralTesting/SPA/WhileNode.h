#pragma once
#include "StatementNode.h"

class WhileNode: public StatementNode {
public:
	explicit WhileNode(int lineNumber);
	~WhileNode() override;

	// pozwala tylko na 2 childy: VariableNode i StmLstNode
	void addChild(Node* child) override;
};
