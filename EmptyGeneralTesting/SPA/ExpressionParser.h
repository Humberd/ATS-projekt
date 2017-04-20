#pragma once
#include <vector>
#include "LexerToken.h"
#include "Node.h"
#include "ParsingEntity.h"

using namespace std;

class ExpressionParser: public ParsingEntity {
public:
	explicit ExpressionParser(vector<LexerToken*>::iterator& iterator,
	                          vector<LexerToken*>::iterator& iteratorEnd);
	~ExpressionParser();
	Node* parse() override;
};
