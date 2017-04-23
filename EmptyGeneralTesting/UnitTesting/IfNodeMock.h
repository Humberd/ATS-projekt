#pragma once
#include "../SPA/StatementNode.h"

class IfNodeMock : public StatementNode {
public:
	explicit IfNodeMock(int lineNumber);
	~IfNodeMock();

	void addChild(Node* child) override;
};
