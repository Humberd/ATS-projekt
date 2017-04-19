#pragma once
#include "Node.h"
#include "LexerToken.h"
#include "ParsersRepository.h"

using namespace std;

class SourceParser {
private:
	ParsersRepository* parsersRepo;
	vector<LexerToken*>& tokensList;

public:
	explicit SourceParser(vector<LexerToken*>& tokensList);
	~SourceParser();
	Node* parse();
};
