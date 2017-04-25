#pragma once
#include "Node.h"

class StatementListNode: public Node {
public:
	explicit StatementListNode(int sourceLineNumber, int programLineNumber);
	~StatementListNode() override;

	//pozwala na 1 lub wi�cej StatementNode
	void addChild(Node* child) override;
};
