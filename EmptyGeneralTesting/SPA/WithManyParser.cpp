#include "WithManyParser.h"
#include "QParsersRepository.h"
#include "QParserException.h"

WithManyParser::WithManyParser(QParsersRepository* parsersRepo,
                               vector<QLexerToken*>::iterator& lexerToken,
                               vector<QLexerToken*>::iterator& iteratorEnd) : QParsingEntity(parsersRepo, lexerToken, iteratorEnd) {
}

WithManyParser::~WithManyParser() {
}

vector<WithRequest*> WithManyParser::parse() {
	vector<WithRequest*> result;

	throwOnEOF();

	if ((*iterator)->isWith()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a 'with' keyword, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	while (iterator != iteratorEnd) {
		result.push_back(parsersRepo->withParser->parse());

		if (iterator == iteratorEnd) {
			break;
		} else if ((*iterator)->isAnd()) {
			nextElement();
			throwOnEOF();
			continue;
		} else {
			throw QParserException(getClassName() + " - unexpected token, but instead got: " + (*iterator)->toString());
		}
	}

	return result;
}
