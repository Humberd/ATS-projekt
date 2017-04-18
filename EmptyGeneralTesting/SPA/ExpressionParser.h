#pragma once
#include "ParsingEntity.h"

class ExpressionParser: public ParsingEntity {
public:
	ExpressionParser();
	~ExpressionParser();

	Node* parseEntity(vector<LexerToken*>::iterator& iterator) override;
};
