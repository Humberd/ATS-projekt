#pragma once
#include "Node.h"


class ProgramNode : Node {

public:
	explicit ProgramNode();
	~ProgramNode();

	//pozwala na 1 lub wiêcej ProcedureNode
	void addChild(Node* child) override;

};
