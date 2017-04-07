#pragma once
#include "ExprNode.h"

class TimesNode: public ExprNode {
public:
	TimesNode();
	~TimesNode();

	void addChild(Node* child) override;
	void validate() override;
};
