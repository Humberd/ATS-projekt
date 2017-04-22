#include "IfParser.h"
#include "ParsersRepository.h"
#include "ParserException.h"

IfParser::IfParser(ParsersRepository* parsersRepo,
                   vector<LexerToken*>::iterator& iterator,
                   vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

IfParser::~IfParser() {
}

Node* IfParser::parse() {
	throw ParserException("fd");
}
