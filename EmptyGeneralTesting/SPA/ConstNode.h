#pragma once
#include "Node.h"

class ConstNode: public Node {
private:
	int value;

public:
	explicit ConstNode(int value);
	~ConstNode() override;


	void setValue(int value);
	int getValue();

	void addChild(Node* child) override;
	void validate() override;
};
