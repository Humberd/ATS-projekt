#pragma once
#include <vector>
#include "LexerToken.h"
#include "Node.h"

using namespace std;

class ParsingEntity {
protected:
	ParsingEntity();

public:
	virtual ~ParsingEntity();

	virtual Node* parseEntity(vector<LexerToken*>::iterator& iterator) = 0;

	void nextElement(vector<LexerToken*>::iterator& iterator) const;

	string getClassName();
};
