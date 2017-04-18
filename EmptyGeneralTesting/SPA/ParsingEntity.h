#pragma once
#include <vector>
#include "LexerToken.h"

using namespace std;

template <class T>
class ParsingEntity {
protected:
	ParsingEntity();

public:
	virtual ~ParsingEntity();

	virtual T* parseEntity(vector<LexerToken*>::iterator& iterator) = 0;

	void nextElement(vector<LexerToken*>::iterator& iterator) const;
};
