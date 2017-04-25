#pragma once
#include "../SPA/ProcedureNode.h"

class ProcedureNodeMock : public ProcedureNode {
public:
	explicit ProcedureNodeMock(int sourceLineNumber, int programLineNumber);
	~ProcedureNodeMock();

	void addChild(Node* child) override;
};
