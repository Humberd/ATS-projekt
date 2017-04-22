#include "WhileParser.h"
#include "ParsersRepository.h"

WhileParser::WhileParser(ParsersRepository* parsersRepo,
                         vector<LexerToken*>::iterator& iterator,
                         vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

WhileParser::~WhileParser() {
}

Node* WhileParser::parse() {
	return nullptr;
}
