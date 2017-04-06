#pragma once
#include "Node.h"

class StmtListNode: Node {
private:
	int lineNumber;

public:
	explicit StmtListNode();
	~StmtListNode();

	void setLineNumber(int lineNumber);
	int getLineNumber();

	//pozwala na 1 lub wiêcej ExprNode
	void addChild(Node* child) override;
};
