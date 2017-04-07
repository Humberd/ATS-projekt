#pragma once
#include "StatementNode.h"

class CallNode: public StatementNode {
public:
	CallNode();
	~CallNode();

	// pozwala tylko na 0 childow
	void addChild(Node* child) override;
	void validate() override;
};
