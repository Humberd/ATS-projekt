#pragma once
#include "Node.h"
#include "LexerToken.h"

//using namespace std;

class Parser {
private:
	Parser();
	~Parser();

	static void parse(vector<LexerToken*>::iterator& iterator,
	                  vector<LexerToken*>::iterator& iteratorEnd,
	                  Node* parentNode);

public:

	static Node* parse(vector<LexerToken*>& tokensList);
};
