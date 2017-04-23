#pragma once
#include "ParsingEntity.h"

class ParsersRepository;

class WhileParser: public ParsingEntity {

public:
	explicit WhileParser(ParsersRepository* parsersRepo,
	                     vector<LexerToken*>::iterator& iterator,
	                     vector<LexerToken*>::iterator& iteratorEnd);

	~WhileParser();

	Node* parse() override;
};
