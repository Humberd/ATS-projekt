#include "stdafx.h"
#include "IfParserMock.h"
#include "../SPA/ParsersRepository.h"
#include "IfNodeMock.h"
#include "../SPA/ParserException.h"
#include "TokenKeyMocks.h"

IfParserMock::IfParserMock(ParsersRepository* parsersRepo,
                           vector<LexerToken*>::iterator& iterator,
                           vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

IfParserMock::~IfParserMock() {
}

Node* IfParserMock::parse() {
	throwOnEOF();

	if ((*iterator)->getKey() == TokenKeyMocks::IF_MOCK) {
		nextElement();
		return new IfNodeMock(1, 1);
	} else {
		throw ParserException("exc");
	}
}
