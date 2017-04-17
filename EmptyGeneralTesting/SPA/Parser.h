#pragma once
#include "Node.h"
#include "LexerToken.h"

//using namespace std;

class Parser {
private:
	Parser();
	~Parser();

public:

	static Node* parse(vector<LexerToken*>& tokensList);

	static Node* parseCall(vector<LexerToken*>::iterator& iterator,
	                       vector<LexerToken*>::iterator& iteratorEnd);

	static Node* parseCallBetter(vector<LexerToken*>::iterator& iterator,
	                             vector<LexerToken*>::iterator& iteratorEnd);
};
