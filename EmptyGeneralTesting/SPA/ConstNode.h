#pragma once
#include "Node.h"

class ConstNode: Node {
private:
	int value;

public:
	explicit ConstNode();
	~ConstNode() override;


	void setValue(int value);
	int getValue();


	void addChild(Node* child) override;
};
