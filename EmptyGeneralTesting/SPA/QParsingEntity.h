#pragma once
#include <vector>
#include "QLexerToken.h"
#include "QueryRequest.h"

using namespace std;

class QParsersRepository;

class QParsingEntity {
protected:
	QParsersRepository* parsersRepo;
	vector<QLexerToken*>::iterator& iterator;
	vector<QLexerToken*>::iterator& iteratorEnd;

	QParsingEntity(QParsersRepository* parsersRepo,
	               vector<QLexerToken*>::iterator& lexerToken,
	               vector<QLexerToken*>::iterator& iteratorEnd);

public:
	virtual ~QParsingEntity();

	void nextElement() const;

	void throwOnEOF() const;

	string getClassName() const;
};
