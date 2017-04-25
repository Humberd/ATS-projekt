#pragma once
#include "../SPA/StatementNode.h"

class AssignNodeMock : public StatementNode {
public:
	explicit AssignNodeMock(int sourceLineNumber, int programLineNumber);
	~AssignNodeMock();

	void addChild(Node* child) override;
};
