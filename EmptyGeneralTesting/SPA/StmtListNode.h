#pragma once
#include "Node.h"

class StmtListNode: public Node {
private:
	int lineNumber;

public:
	explicit StmtListNode(int lineNumber);
	~StmtListNode();

	void setLineNumber(int lineNumber);
	int getLineNumber();

	//pozwala na 1 lub wiêcej ExprNode
	void addChild(Node* child) override;
	void validate() override;
};
