#pragma once
#include "QLexerToken.h"
#include <vector>
#include "DeclaredVariable.h"

class DParsersRepository;
using namespace std;

class DParsingEntity {
protected:
	DParsersRepository* parsersRepo;
	vector<QLexerToken*>::iterator& iterator;
	vector<QLexerToken*>::iterator& iteratorEnd;

	DParsingEntity(DParsersRepository* parsersRepo,
	               vector<QLexerToken*>::iterator& lexerToken,
	               vector<QLexerToken*>::iterator& iteratorEnd);

public:
	virtual ~DParsingEntity();

	virtual DeclaredVariable* parse() = 0;

	void nextElement() const;

	void throwOnEOF() const;

	string getClassName() const;
};
