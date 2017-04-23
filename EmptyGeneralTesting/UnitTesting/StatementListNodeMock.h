#pragma once
#include "../SPA/Node.h"

class StatementListNodeMock : public Node {
public:
	explicit StatementListNodeMock(int lineNumber);
	~StatementListNodeMock();

	void addChild(Node* child) override;
};
