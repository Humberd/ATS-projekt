#pragma once
#include "../SPA/Node.h"
#include "../SPA/ParsingEntity.h"

class ParsersRepository;

class StatementListParserMock : public ParsingEntity {
public:
	StatementListParserMock(ParsersRepository* parsersRepo,
	                        vector<LexerToken*>::iterator& iterator,
	                        vector<LexerToken*>::iterator& iteratorEnd);
	~StatementListParserMock();

	Node* parse() override;
};
