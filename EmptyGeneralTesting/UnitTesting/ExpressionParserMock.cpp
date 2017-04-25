#include "stdafx.h"
#include "ExpressionParserMock.h"
#include "ExpressionNodeMock.h"
#include "../SPA/ParsersRepository.h"
#include "../SPA/ParserException.h"
#include "TokenKeyMocks.h"

ExpressionParserMock::ExpressionParserMock(ParsersRepository* parsersRepo, vector<LexerToken*>::iterator& iterator, vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

ExpressionParserMock::~ExpressionParserMock() {
}

Node* ExpressionParserMock::parse() {
	throwOnEOF();

	if ((*iterator)->getKey() == TokenKeyMocks::EXPRESSION_MOCK) {
		nextElement();
		return new ExpressionNodeMock(1, 1);
	} else {
		throw ParserException("exc");
	}
}
