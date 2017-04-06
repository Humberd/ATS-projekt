#pragma once
#include "Node.h"

class StmtNode: public Node {
public:
	explicit StmtNode();
	virtual ~StmtNode() = 0;

	virtual void addChild(Node* child) override;
};
