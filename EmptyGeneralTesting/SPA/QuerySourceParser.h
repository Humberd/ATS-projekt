#pragma once
#include "QParsingEntity.h"

class QParsersRepository;

class QuerySourceParser: public QParsingEntity {
public:

	QuerySourceParser(QParsersRepository* parsersRepo,
	                  vector<QLexerToken*>::iterator& lexerToken,
	                  vector<QLexerToken*>::iterator& iteratorEnd);
	~QuerySourceParser();

	QueryRequest* parse() const;
};
