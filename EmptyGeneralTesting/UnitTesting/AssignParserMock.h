#pragma once
#include "../SPA/Node.h"
#include "../SPA/ParsingEntity.h"

class ParsersRepository;

class AssignParserMock : public ParsingEntity {
public:
	explicit AssignParserMock(ParsersRepository* parsersRepo,
	                          vector<LexerToken*>::iterator& iterator,
	                          vector<LexerToken*>::iterator& iteratorEnd);
	~AssignParserMock();

	Node* parse() override;
};
