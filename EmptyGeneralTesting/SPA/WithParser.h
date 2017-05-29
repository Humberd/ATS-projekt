#pragma once
#include "QParsingEntity.h"
#include "WithRequest.h"

class QParsersRepository;

class WithParser: public QParsingEntity {
public:

	explicit WithParser(QParsersRepository* parsersRepo,
	                    vector<QLexerToken*>::iterator& lexerToken,
	                    vector<QLexerToken*>::iterator& iteratorEnd);
	~WithParser();

	WithRequest* parse() const;
};
