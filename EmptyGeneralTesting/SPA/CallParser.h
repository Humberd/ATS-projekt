#pragma once
#include "ParsingEntity.h"

class ParsersRepository;

class CallParser: public ParsingEntity {

public:
	explicit CallParser(ParsersRepository* parsersRepo,
	                    vector<LexerToken*>::iterator& iterator,
	                    vector<LexerToken*>::iterator& iteratorEnd);

	~CallParser();

	Node* parse() override;
};
