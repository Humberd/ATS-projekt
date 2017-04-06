#pragma once
#include "StmtNode.h"

class CallNode: StmtNode {
public:
	explicit CallNode();
	~CallNode() override;


	void addChild(Node* child) override;
};
