#include "Parser.h"
#include "ProgramNode.h"
#include "ParserException.h"

Parser::Parser() {
}

Parser::~Parser() {
}

Node* Parser::parse(vector<LexerToken*>& tokensList) {
	auto iterator = tokensList.begin();
	auto iteratorEnd = tokensList.end();

	return nullptr;;
}
