#pragma once
#include "ParsingEntity.h"

class ParsersRepository;

class IfParser: public ParsingEntity {

public:
	IfParser(ParsersRepository* parsersRepo,
	         vector<LexerToken*>::iterator& iterator,
	         vector<LexerToken*>::iterator& iteratorEnd);

	~IfParser();

	Node* parse() override;
};
