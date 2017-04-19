#pragma once
#include <vector>
#include "LexerToken.h"
#include "Node.h"

using namespace std;

class ParsingEntity {
private:
	vector<LexerToken*>::iterator& iterator;
	vector<LexerToken*>::iterator& iteratorEnd;

protected:
	explicit ParsingEntity(vector<LexerToken*>::iterator& iterator,
	              vector<LexerToken*>::iterator& iteratorEnd);

public:
	virtual ~ParsingEntity();

	virtual Node* parse() = 0;

	void nextElement() const;

	string getClassName() const;
};
