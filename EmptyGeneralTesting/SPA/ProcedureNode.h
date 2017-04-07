#pragma once
#include "Node.h"

using namespace std;

class ProdecureNode : public Node {
private:
	string name;

public:
	explicit ProdecureNode(string name);
	~ProdecureNode();

	void setName(string name);
	string getName();

	// pozwala tylko na 1 StmLstNode
	void addChild(Node* child) override;
	void validate() override;
};
