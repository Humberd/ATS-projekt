#pragma once
#include "../SPA/Node.h"
#include "../SPA/ParsingEntity.h"

class ParsersRepository;

class ExpressionParserMock : public ParsingEntity {
public:
	explicit ExpressionParserMock(ParsersRepository* parsersRepo,
	                              vector<LexerToken*>::iterator& iterator,
	                              vector<LexerToken*>::iterator& iteratorEnd);
	~ExpressionParserMock();

	Node* parse() override;
};
