#include "stdafx.h"
#include "ExpressionParserMock.h"
#include "ExpressionNodeMock.h"
#include "../SPA/ParsersRepository.h"

ExpressionParserMock::ExpressionParserMock(ParsersRepository* parsersRepo, vector<LexerToken*>::iterator& iterator, vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

ExpressionParserMock::~ExpressionParserMock() {
}

Node* ExpressionParserMock::parse() {
	return new ExpressionNodeMock(1);
}

