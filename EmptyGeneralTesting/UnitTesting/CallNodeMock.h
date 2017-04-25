#pragma once
#include "../SPA/StatementNode.h"

class CallNodeMock : public StatementNode {
public:
	explicit CallNodeMock(int sourceLineNumber, int programLineNumber);
	~CallNodeMock();

	void addChild(Node* child) override;
};
