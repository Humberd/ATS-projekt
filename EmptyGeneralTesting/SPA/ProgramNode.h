#pragma once
#include "Node.h"


class ProgramNode : public Node {

public:

	explicit ProgramNode(int sourceLineNumber);
	~ProgramNode() override;

	//pozwala na 1 lub wiêcej ProcedureNode
	void addChild(Node* child) override;
};
