#pragma once
#include <vector>
#include "LexerToken.h"
#include "Node.h"

using namespace std;

class ParsersRepository;

class ParsingEntity {
protected:
	ParsersRepository* parsersRepo;
	vector<LexerToken*>::iterator& iterator;
	vector<LexerToken*>::iterator& iteratorEnd;

	explicit ParsingEntity(ParsersRepository* parsersRepo,
	                       vector<LexerToken*>::iterator& iterator,
	                       vector<LexerToken*>::iterator& iteratorEnd);

public:
	virtual ~ParsingEntity();

	virtual Node* parse() = 0;

	void nextElement() const;

	string getClassName() const;
};