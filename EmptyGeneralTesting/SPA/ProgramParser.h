#pragma once
#include "ParsingEntity.h"

class ParsersRepository;

class ProgramParser: public ParsingEntity {

public:
	ProgramParser(ParsersRepository* parsersRepo,
	              vector<LexerToken*>::iterator& iterator,
	              vector<LexerToken*>::iterator& iteratorEnd);
	~ProgramParser();

	Node* parse() override;
};
