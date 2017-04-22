#pragma once
#include "ParsingEntity.h"

class ParsersRepository;

class StatementListParser: public ParsingEntity {

public:
	StatementListParser(ParsersRepository* parsersRepo,
	                    vector<LexerToken*>::iterator& iterator,
	                    vector<LexerToken*>::iterator& iteratorEnd);

	~StatementListParser();

	Node* parse() override;
};
