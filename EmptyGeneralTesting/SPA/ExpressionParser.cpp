#include "ExpressionParser.h"


ExpressionParser::ExpressionParser(vector<LexerToken*>::iterator& iterator,
                                   vector<LexerToken*>::iterator& iteratorEnd): ExpressionParser(iterator, iteratorEnd) {
}

ExpressionParser::~ExpressionParser() {
}

Node* ExpressionParser::parse() {
	return nullptr;
}
