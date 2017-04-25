#pragma once
#include "Node.h"
#include "ReferenceNode.h"

using namespace std;

class VariableNode : public ReferenceNode {
private:
	string name;

public:
	explicit VariableNode(int sourceLineNumber, int programLineNumber, string name);
	~VariableNode() override;

	void setName(string name);
	string getName() const;

	// pozwala na 0 childow
	void addChild(Node* child) override;

	string toString() const override;
};
