#include "SelectParser.h"

SelectParser::SelectParser(QParsersRepository* parsersRepo,
                           vector<QLexerToken*>::iterator& lexerToken,
                           vector<QLexerToken*>::iterator& iteratorEnd): QParsingEntity(parsersRepo, lexerToken, iteratorEnd) {
}

SelectParser::~SelectParser() {
}

void SelectParser::parse() {
}
