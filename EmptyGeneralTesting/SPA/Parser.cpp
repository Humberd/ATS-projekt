#include "Parser.h"
#include "ProgramNode.h"

Parser::Parser() {
}

Parser::~Parser() {
}

Node* Parser::parse(vector<LexerToken*>& tokensList) {
	auto iterator = tokensList.begin();
	auto iteratorEnd = tokensList.end();

	Node* rootNode = new ProgramNode(0);

	parse(iterator, iteratorEnd, rootNode);

	return rootNode;
}

void Parser::parse(vector<LexerToken*>::iterator& iterator,
                    vector<LexerToken*>::iterator& iteratorEnd,
                    Node* parentNode) {
}
