#pragma once
#include "StmtNode.h"

class WhileNode: StmtNode {
public:
	explicit WhileNode();
	~WhileNode() override;


	void addChild(Node* child) override;
};
