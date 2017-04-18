#pragma once
#include "Node.h"
#include "LexerToken.h"

//using namespace std;

class SourceParser {
private:
	SourceParser();
	~SourceParser();

public:

	static Node* parse(vector<LexerToken*>& tokensList);

	static Node* parseCall(vector<LexerToken*>::iterator& iterator);

	static Node* parseAssign(vector<LexerToken*>::iterator& iterator);

	static Node* parseExpression(vector<LexerToken*>::iterator& iterator);

	static void nextElement(string name,
	                        vector<LexerToken*>::iterator& iterator);
};
