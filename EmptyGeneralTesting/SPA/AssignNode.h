#pragma once
#include "StmtNode.h"

class AssignNode: StmtNode {

public:
	explicit AssignNode();
	~AssignNode() override;

	void addChild(Node* child) override;
};
