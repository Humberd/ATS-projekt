#pragma once
#include "Node.h"

class StatementListNode: public Node {
private:
	int lineNumber;

public:
	explicit StatementListNode(int lineNumber);
	~StatementListNode();

	void setLineNumber(int lineNumber);
	int getLineNumber();

	//pozwala na 1 lub wiêcej ExpressionNode
	void addChild(Node* child) override;
	void validate() override;
};
