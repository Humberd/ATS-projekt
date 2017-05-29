#pragma once
#include "../SPA/StatementNode.h"

class CallNodeMock : public StatementNode {
public:
	explicit CallNodeMock(int sourceLineNumber);
	~CallNodeMock();

	void addChild(Node* child) override;
};
