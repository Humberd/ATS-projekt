#pragma once
#include "../SPA/StatementNode.h"

class AssignNodeMock : public StatementNode {
public:
	explicit AssignNodeMock(int lineNumber);
	~AssignNodeMock();

	void addChild(Node* child) override;
};
