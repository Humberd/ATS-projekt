#pragma once
#include "../SPA/Node.h"
#include "../SPA/ParsingEntity.h"

class ParsersRepository;

class WhileParserMock : public ParsingEntity {
public:
	explicit WhileParserMock(ParsersRepository* parsersRepo,
	                         vector<LexerToken*>::iterator& iterator,
	                         vector<LexerToken*>::iterator& iteratorEnd);
	~WhileParserMock();

	Node* parse() override;
};
