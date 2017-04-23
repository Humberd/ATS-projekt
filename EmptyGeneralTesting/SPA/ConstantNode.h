#pragma once
#include "Node.h"
#include "ReferenceNode.h"

class ConstantNode: public ReferenceNode {
private:
	int value;

public:
	explicit ConstantNode(int lineNumber, int value);
	~ConstantNode() override;

	void setValue(int value);
	int getValue() const;

	// pozwala na 0 childow
	void addChild(Node* child) override;


	string toString() const override;
};
