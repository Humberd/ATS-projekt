#pragma once
#include "../SPA/ProcedureNode.h"

class ProcedureNodeMock : public ProcedureNode {
public:
	explicit ProcedureNodeMock(int sourceLineNumber);
	~ProcedureNodeMock();

	void addChild(Node* child) override;
};
