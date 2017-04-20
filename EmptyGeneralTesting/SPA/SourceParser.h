#pragma once
#include <vector>
#include "LexerToken.h"
#include "Node.h"
#include "ParsersRepository.h"

using namespace std;

class SourceParser {
private:
	vector<LexerToken*>& tokensList;

public:
	explicit SourceParser(vector<LexerToken*>& tokensList);
	~SourceParser();
	Node* parse();
};
