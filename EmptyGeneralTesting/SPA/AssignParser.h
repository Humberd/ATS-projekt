#pragma once
#include "ParsingEntity.h"

using namespace std;

class ParsersRepository;

class AssignParser: public ParsingEntity {
public:
	AssignParser(ParsersRepository* parsersRepo,
	             vector<LexerToken*>::iterator& iterator,
	             vector<LexerToken*>::iterator& iteratorEnd);
	~AssignParser();

	Node* parse() override;
};
