#pragma once
#include "Node.h"

class StmtNode: public Node {
protected:
	StmtNode();

public:
	virtual ~StmtNode() = 0;
};
