#include "MethodManyParser.h"
#include "QParsersRepository.h"
#include "QParserException.h"

MethodManyParser::MethodManyParser(QParsersRepository* parsersRepo,
                                   vector<QLexerToken*>::iterator& lexerToken,
                                   vector<QLexerToken*>::iterator& iteratorEnd) : QParsingEntity(parsersRepo, lexerToken, iteratorEnd) {
}

MethodManyParser::~MethodManyParser() {
}

vector<MethodRequest*> MethodManyParser::parse() {
	vector<MethodRequest*> result;

	throwOnEOF();

	if ((*iterator)->isSuch()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a 'such' keyword, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isThat()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a 'that' keyword, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	while (iterator != iteratorEnd) {
		result.push_back(parsersRepo->methodParser->parse());

		if (iterator == iteratorEnd) {
			break;
		} else if ((*iterator)->isAnd()) {
			nextElement();
			throwOnEOF();
			continue;
		} else {
			break;
		}
	}

	return result;
}
