#pragma once
#include "StatementNode.h"

class CallNode: public StatementNode {
private:
	string procedureName;

public:
	explicit CallNode(string procedureName);
	~CallNode() override;


	string getProcedureName() const;
	void setProcedureName(string procedureName);

	// pozwala tylko na 0 childow
	void addChild(Node* child) override;
	void validate() override;
};
