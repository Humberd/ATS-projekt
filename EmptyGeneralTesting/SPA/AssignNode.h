#pragma once
#include "StmtNode.h"

class AssignNode: public StmtNode {

public:
	AssignNode();
	~AssignNode() ;

	void addChild(Node* child) override;
	void validate() override;
};
