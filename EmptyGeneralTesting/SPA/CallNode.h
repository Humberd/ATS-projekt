#pragma once
#include "StmtNode.h"

class CallNode: public StmtNode {
public:
	CallNode();
	~CallNode();


	void addChild(Node* child) override;
};
