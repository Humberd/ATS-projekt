#pragma once
#include "StmtNode.h"

class IfNode: public StmtNode {

public:
	IfNode();
	~IfNode();

	void addChild(Node* child) override;
	void validate() override;
};
