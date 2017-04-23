#pragma once
#include "../SPA/StatementNode.h"

class CallNodeMock : public StatementNode {
public:
	explicit CallNodeMock(int lineNumber);
	~CallNodeMock();

	void addChild(Node* child) override;
};
