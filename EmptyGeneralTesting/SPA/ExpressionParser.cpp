#include "ExpressionParser.h"

ExpressionParser::ExpressionParser(ParsersRepository* parsersRepo,
                                   vector<LexerToken*>::iterator& iterator,
                                   vector<LexerToken*>::iterator& iteratorEnd): ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

ExpressionParser::~ExpressionParser() {
}

Node* ExpressionParser::parse() {
	return nullptr;
}
