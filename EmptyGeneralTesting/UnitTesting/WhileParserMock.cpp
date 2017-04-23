#include "stdafx.h"
#include "WhileParserMock.h"
#include "../SPA/ParsersRepository.h"

WhileParserMock::WhileParserMock(ParsersRepository* parsersRepo,
                                 vector<LexerToken*>::iterator& iterator,
                                 vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

WhileParserMock::~WhileParserMock() {
}

Node* WhileParserMock::parse() {
	return nullptr;
}
