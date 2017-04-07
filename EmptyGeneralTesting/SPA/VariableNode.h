#pragma once
#include "Node.h"

using namespace std;

class VarNode : public Node {
private:
	string name;

public:
	explicit VarNode(string name);
	~VarNode();

	void setName(string name);
	string getName();

	void addChild(Node* child) override;
	void validate() override;
};
