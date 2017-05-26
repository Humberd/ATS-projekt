#pragma once
#include "QParsingEntity.h"

class VariableParser: public QParsingEntity {
public:

	VariableParser(QParsersRepository* parsersRepo,
	               vector<QLexerToken*>::iterator& lexerToken,
	               vector<QLexerToken*>::iterator& iteratorEnd);

	~VariableParser();

	QueryVariable* parse();
};
