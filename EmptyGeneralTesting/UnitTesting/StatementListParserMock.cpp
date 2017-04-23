#include "stdafx.h"
#include "StatementListParserMock.h"
#include "../SPA/ParsersRepository.h"
#include "StatementListNodeMock.h"
#include "../SPA/ParserException.h"
#include "TokenKeyMocks.h"

StatementListParserMock::StatementListParserMock(ParsersRepository* parsersRepo,
                                                 vector<LexerToken*>::iterator& iterator,
                                                 vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

StatementListParserMock::~StatementListParserMock() {
}

Node* StatementListParserMock::parse() {
	throwOnEOF();

	if ((*iterator)->getKey() == TokenKeyMocks::STATEMENT_LIST_MOCK) {
		nextElement();
		return new StatementListNodeMock(1);
	} else {
		throw ParserException("exc");
	}
}
