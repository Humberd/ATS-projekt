#pragma once
#include "Node.h"

class ConstantNode: public Node {
private:
	int value;

public:
	explicit ConstantNode(int value);
	~ConstantNode() override;

	void setValue(int value);
	int getValue() const;

	// pozwala na 0 childow
	void addChild(Node* child) override;
	void validate() override;
};
