#pragma once
#include "../SPA/StatementNode.h"

class IfNodeMock : public StatementNode {
public:
	explicit IfNodeMock(int sourceLineNumber);
	~IfNodeMock();

	void addChild(Node* child) override;
};
