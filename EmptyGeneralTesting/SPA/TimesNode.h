#pragma once
#include "ExprNode.h"

class TimesNode: ExprNode {
public:
	explicit TimesNode();
	~TimesNode();

	void addChild(Node* child) override;
};
