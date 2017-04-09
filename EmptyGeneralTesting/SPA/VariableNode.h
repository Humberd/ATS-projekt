#pragma once
#include "Node.h"

using namespace std;

class VariableNode : public Node {
private:
	string name;

public:
	explicit VariableNode(string name);
	~VariableNode();

	void setName(string name);
	string getName();

	// pozwala na 0 childow
	void addChild(Node* child) override;
	void validate() override;
};
