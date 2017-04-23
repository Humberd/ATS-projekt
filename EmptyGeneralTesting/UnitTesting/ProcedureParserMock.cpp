#include "stdafx.h"
#include "../SPA/ParsersRepository.h"
#include "../SPA/ParserException.h"
#include "TokenKeyMocks.h"
#include "ProcedureParserMock.h"
#include "ProcedureNodeMock.h"

ProcedureParserMock::ProcedureParserMock(ParsersRepository* parsersRepo,
                                         vector<LexerToken*>::iterator& iterator,
                                         vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

ProcedureParserMock::~ProcedureParserMock() {
}

Node* ProcedureParserMock::parse() {
	throwOnEOF();

	if ((*iterator)->getKey() == TokenKeyMocks::PROCEDURE_MOCK) {
		nextElement();
		return new ProcedureNodeMock(1);
	} else {
		throw ParserException("exc");
	}
}
