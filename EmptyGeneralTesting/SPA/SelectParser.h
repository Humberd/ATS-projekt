#pragma once
#include "QParsingEntity.h"

class QParsersRepository;

class SelectParser: public QParsingEntity {

public:

	SelectParser(QParsersRepository* parsersRepo,
	             vector<QLexerToken*>::iterator& lexerToken,
	             vector<QLexerToken*>::iterator& iteratorEnd);

	~SelectParser();

	ReturnRequest* parse();
	vector<QueryVariable*> parseTouple();
};
