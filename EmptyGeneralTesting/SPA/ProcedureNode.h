#pragma once
#include "Node.h"

using namespace std;

class ProdecureNode : Node {
private:
	string name;

public:
	explicit ProdecureNode();
	~ProdecureNode();

	void setName(string name);
	string getName();

	// pozwala tylko na 1 StmLstNode
	void addChild(Node* child) override;
};
