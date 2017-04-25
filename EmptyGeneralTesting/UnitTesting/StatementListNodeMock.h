#pragma once
#include "../SPA/Node.h"
#include "../SPA/StatementListNode.h"

class StatementListNodeMock : public StatementListNode {
public:
	explicit StatementListNodeMock(int sourceLineNumber, int programLineNumber);
	~StatementListNodeMock();

	void addChild(Node* child) override;
};
