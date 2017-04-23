#pragma once
#include "../SPA/StatementNode.h"
#include "../SPA/ProcedureNode.h"

class ProcedureNodeMock : public ProcedureNode {
public:
	explicit ProcedureNodeMock(int lineNumber);
	~ProcedureNodeMock();

	void addChild(Node* child) override;
};
