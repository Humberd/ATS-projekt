#pragma once
#include "../SPA/Node.h"
#include "../SPA/Constants.h"

class CallsNode: public Node {
private:
	PROC proc;

public:
	explicit CallsNode(PROC proc);
	~CallsNode() override;

	void setProc(PROC proc);
	PROC getProc() const;

	void addChild(Node* child) override;
	void addChildren(vector<PROC> children);
};