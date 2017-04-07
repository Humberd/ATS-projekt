#pragma once
#include "StmtNode.h"

class WhileNode: public StmtNode {
public:
	WhileNode();
	~WhileNode();

	void addChild(Node* child) override;
	void validate() override;
};
