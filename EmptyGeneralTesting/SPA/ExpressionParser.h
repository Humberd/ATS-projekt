#pragma once
#include "ParsingEntity.h"

class ExpressionParser: public ParsingEntity {
public:
	explicit ExpressionParser(vector<LexerToken*>::iterator& iterator, vector<LexerToken*>::iterator& iteratorEnd);

	~ExpressionParser();

	Node* parse() override;
};
