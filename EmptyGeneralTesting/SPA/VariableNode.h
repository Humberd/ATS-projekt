#pragma once
#include "Node.h"

using namespace std;

class VarNode: Node {
private:
	string name;

public:
	explicit VarNode();
	~VarNode();

	void setName(string name);
	string getName();

	void addChild(Node* child) override;
};
