#include "stdafx.h"
#include "WhileParserMock.h"
#include "../SPA/ParsersRepository.h"
#include "WhileNodeMock.h"
#include "../SPA/ParserException.h"
#include "TokenKeyMocks.h"

WhileParserMock::WhileParserMock(ParsersRepository* parsersRepo,
                                 vector<LexerToken*>::iterator& iterator,
                                 vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

WhileParserMock::~WhileParserMock() {
}

Node* WhileParserMock::parse() {
	throwOnEOF();

	if ((*iterator)->getKey() == TokenKeyMocks::WHILE_MOCK) {
		nextElement();
		return new WhileNodeMock(1, 1);
	} else {
		throw ParserException("exc");
	}
}
