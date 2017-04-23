#include "stdafx.h"
#include "IfParserMock.h"
#include "../SPA/ParsersRepository.h"

IfParserMock::IfParserMock(ParsersRepository* parsersRepo,
                           vector<LexerToken*>::iterator& iterator,
                           vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

IfParserMock::~IfParserMock() {
}

Node* IfParserMock::parse() {
	return nullptr;
}
