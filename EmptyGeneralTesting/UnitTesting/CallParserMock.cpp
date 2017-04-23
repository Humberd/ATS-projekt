#include "stdafx.h"
#include "CallParserMock.h"
#include "../SPA/ParsersRepository.h"

CallParserMock::CallParserMock(ParsersRepository* parsersRepo,
                               vector<LexerToken*>::iterator& iterator,
                               vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

CallParserMock::~CallParserMock() {
}

Node* CallParserMock::parse() {
	return nullptr;
}
