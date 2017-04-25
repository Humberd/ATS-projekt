#pragma once
#include "../SPA/StatementNode.h"

class WhileNodeMock : public StatementNode {
public:
	explicit WhileNodeMock(int sourceLineNumber, int programLineNumber);
	~WhileNodeMock();

	void addChild(Node* child) override;
};
