#include "stdafx.h"
#include "AssignParserMock.h"
#include "../SPA/ParsersRepository.h"

AssignParserMock::AssignParserMock(ParsersRepository* parsersRepo,
                                   vector<LexerToken*>::iterator& iterator,
                                   vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

AssignParserMock::~AssignParserMock() {
}

Node* AssignParserMock::parse() {
	return nullptr;
}
