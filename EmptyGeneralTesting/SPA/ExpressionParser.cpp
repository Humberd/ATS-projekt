#include "ExpressionParser.h"

ExpressionParser::ExpressionParser(vector<LexerToken*>::iterator& iterator,
                                   vector<LexerToken*>::iterator& iteratorEnd): ParsingEntity(iterator, iteratorEnd) {
}

ExpressionParser::~ExpressionParser() {
}

Node* ExpressionParser::parse() {
	return nullptr;
}
