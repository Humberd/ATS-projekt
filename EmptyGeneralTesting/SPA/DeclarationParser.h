#pragma once
#include "DParsingEntity.h"

class DParsersRepository;

class DeclarationParser: public DParsingEntity {
public:
	DeclarationParser(DParsersRepository* parsersRepo,
	                  vector<QLexerToken*>::iterator& iterator,
	                  vector<QLexerToken*>::iterator& iteratorEnd);

	~DeclarationParser();

	DeclaredVariable* parse() override;
};
