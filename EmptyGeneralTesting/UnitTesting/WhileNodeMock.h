#pragma once
#include "../SPA/StatementNode.h"

class WhileNodeMock : public StatementNode {
public:
	explicit WhileNodeMock(int lineNumber);
	~WhileNodeMock();

	void addChild(Node* child) override;
};
