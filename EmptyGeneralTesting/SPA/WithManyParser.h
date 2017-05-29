#pragma once
#include "QParsingEntity.h"
#include "WithRequest.h"

class QParsersRepository;

class WithManyParser: public QParsingEntity {
public:
	WithManyParser(QParsersRepository* parsersRepo,
	               vector<QLexerToken*>::iterator& lexerToken,
	               vector<QLexerToken*>::iterator& iteratorEnd);
	~WithManyParser();

	vector<WithRequest*> parse();
};
