#pragma once
#include "QParsingEntity.h"

class QParsersRepository;

class MethodParser: public QParsingEntity {
public:
	explicit MethodParser(QParsersRepository* parsersRepo,
	                      vector<QLexerToken*>::iterator& lexerToken,
	                      vector<QLexerToken*>::iterator& iteratorEnd);
	~MethodParser();

	MethodRequest* parse() const;
	Parameter* parseParameter() const;
	string parseString() const;
};
