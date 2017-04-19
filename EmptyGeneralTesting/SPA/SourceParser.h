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
};
