#pragma once
#include "../SPA/StatementNode.h"

class IfNodeMock : public StatementNode {
public:
	explicit IfNodeMock(int sourceLineNumber, int programLineNumber);
	~IfNodeMock();

	void addChild(Node* child) override;
};
