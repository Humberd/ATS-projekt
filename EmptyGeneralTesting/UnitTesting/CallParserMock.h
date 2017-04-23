#pragma once
#include "../SPA/Node.h"
#include "../SPA/ParsingEntity.h"

class ParsersRepository;

class CallParserMock : public ParsingEntity {
public:
	explicit CallParserMock(ParsersRepository* parsersRepo,
	               vector<LexerToken*>::iterator& iterator,
	               vector<LexerToken*>::iterator& iteratorEnd);
	~CallParserMock();

	Node* parse() override;
};
