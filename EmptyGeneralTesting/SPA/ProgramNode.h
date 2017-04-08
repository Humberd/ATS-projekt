#pragma once
#include "Node.h"


class ProgramNode : public Node {

public:
	ProgramNode();
	~ProgramNode();

	//pozwala na 1 lub wiêcej ProcedureNode
	void addChild(Node* child) override;
	void validate() override;
//	string toString() override;
};
