#include "IfParser.h"
#include "ParsersRepository.h"

IfParser::IfParser(ParsersRepository* parsersRepo,
                   vector<LexerToken*>::iterator& iterator,
                   vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

IfParser::~IfParser() {
}

Node* IfParser::parse() {
	return nullptr;;
}
