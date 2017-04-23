#pragma once
#include "../SPA/Node.h"
#include "../SPA/StatementListNode.h"

class StatementListNodeMock : public StatementListNode {
public:
	explicit StatementListNodeMock(int lineNumber);
	~StatementListNodeMock();

	void addChild(Node* child) override;
};
