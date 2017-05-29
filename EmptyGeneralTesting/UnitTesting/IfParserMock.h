#pragma once
#include "../SPA/Node.h"
#include "../SPA/ParsingEntity.h"

class ParsersRepository;

class IfParserMock : public ParsingEntity {
public:
	explicit IfParserMock(ParsersRepository* parsersRepo,
	                      vector<LexerToken*>::iterator& iterator,
	                      vector<LexerToken*>::iterator& iteratorEnd);
	~IfParserMock();

	Node* parse() override;
};
