#pragma once
#include "Node.h"

using namespace std;

class ProcedureNode : public Node {
private:
	string name;

public:
	explicit ProcedureNode(string name);
	~ProcedureNode();

	void setName(string name);
	string getName() const;

	// pozwala tylko na 1 StmLstNode
	void addChild(Node* child) override;
	void validate() override;
};
