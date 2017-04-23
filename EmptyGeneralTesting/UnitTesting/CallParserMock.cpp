#include "stdafx.h"
#include "CallParserMock.h"
#include "../SPA/ParsersRepository.h"
#include "CallNodeMock.h"
#include "../SPA/ParserException.h"
#include "TokenKeyMocks.h"

CallParserMock::CallParserMock(ParsersRepository* parsersRepo,
                               vector<LexerToken*>::iterator& iterator,
                               vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

CallParserMock::~CallParserMock() {
}

Node* CallParserMock::parse() {
	throwOnEOF();

	if ((*iterator)->getKey() == TokenKeyMocks::CALL_MOCK) {
		nextElement();
		return new CallNodeMock(1);
	} else {
		throw ParserException("exc");
	}
}
