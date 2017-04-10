#pragma once
#include "../SPA/Node.h"

class MockNode : public Node {

public:
	~MockNode() override;

	void addChild(Node* child) override;

	void validate() override;
};
