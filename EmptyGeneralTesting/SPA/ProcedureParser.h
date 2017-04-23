#pragma once
#include "ParsingEntity.h"

class ParsersRepository;

class ProcedureParser: public ParsingEntity {

public:
	ProcedureParser(ParsersRepository* parsersRepo,
	                vector<LexerToken*>::iterator& iterator,
	                vector<LexerToken*>::iterator& iteratorEnd);
	~ProcedureParser();

	Node* parse() override;
};
