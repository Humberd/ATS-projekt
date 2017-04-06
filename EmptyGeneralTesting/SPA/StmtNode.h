#pragma once
#include "Node.h"

class StmtNode: Node {
public:
	explicit StmtNode();
	virtual ~StmtNode() = 0;


	virtual void addChild(Node* child) override;
};
