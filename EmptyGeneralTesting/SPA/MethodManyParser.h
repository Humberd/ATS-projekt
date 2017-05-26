#pragma once
#include "QParsingEntity.h"

class QParsersRepository;

class MethodManyParser: public QParsingEntity {
public:

	MethodManyParser(QParsersRepository* parsersRepo,
	                 vector<QLexerToken*>::iterator& lexerToken,
	                 vector<QLexerToken*>::iterator& iteratorEnd);
	~MethodManyParser();

	vector<MethodRequest*> parse();
};
