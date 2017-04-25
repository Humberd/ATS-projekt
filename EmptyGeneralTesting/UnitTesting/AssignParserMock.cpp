#include "stdafx.h"
#include "AssignParserMock.h"
#include "../SPA/ParsersRepository.h"
#include "AssignNodeMock.h"
#include "../SPA/ParserException.h"
#include "TokenKeyMocks.h"

AssignParserMock::AssignParserMock(ParsersRepository* parsersRepo,
                                   vector<LexerToken*>::iterator& iterator,
                                   vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

AssignParserMock::~AssignParserMock() {
}

Node* AssignParserMock::parse() {
	throwOnEOF();

	if ((*iterator)->getKey() == TokenKeyMocks::ASSIGN_MOCK) {
		nextElement();
		return new AssignNodeMock(1, 1);
	} else {
		throw ParserException("exc");
	}
}
