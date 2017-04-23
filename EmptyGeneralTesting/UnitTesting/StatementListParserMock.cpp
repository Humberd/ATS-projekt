#include "stdafx.h"
#include "StatementListParserMock.h"
#include "../SPA/ParsersRepository.h"

StatementListParserMock::StatementListParserMock(ParsersRepository* parsersRepo,
                                                 vector<LexerToken*>::iterator& iterator,
                                                 vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

StatementListParserMock::~StatementListParserMock() {
}

Node* StatementListParserMock::parse() {
	return nullptr;
}
