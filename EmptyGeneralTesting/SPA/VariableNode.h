#pragma once
#include "Node.h"

using namespace std;

class VariableNode : public Node {
private:
	string name;

public:
	explicit VariableNode(string name);
	~VariableNode() override;

	void setName(string name);
	string getName() const;

	// pozwala na 0 childow
	void addChild(Node* child) override;
	void validate() override;
};
