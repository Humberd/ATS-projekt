#include "SelectParser.h"
#include "QParserException.h"

SelectParser::SelectParser(QParsersRepository* parsersRepo,
                           vector<QLexerToken*>::iterator& lexerToken,
                           vector<QLexerToken*>::iterator& iteratorEnd): QParsingEntity(parsersRepo, lexerToken, iteratorEnd) {
}

SelectParser::~SelectParser() {
}

ReturnRequest* SelectParser::parse() {
	ReturnRequest* returnRequest = new ReturnRequest;

	throwOnEOF();

	if ((*iterator)->isSelect()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected 'Select' keyword, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isBoolean()) {
		returnRequest->setReturnType(ReturnType::BOOLEAN);
	} else if ((*iterator)->isSpecialCharacter()) {
		returnRequest->setReturnType(ReturnType::TOUPLE_VARIABLES);
		returnRequest->setToupleVariableNames(parseTouple());
	} else if((*iterator)->isName()) {
		returnRequest->setReturnType(ReturnType::VARIABLE);
		returnRequest->setVariableName((*iterator)->getValue());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isSuch()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected 'such' keyword, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isThat()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected 'that' keyword, but instead got: " + (*iterator)->toString());
	}
	nextElement();

	return returnRequest;
}


vector<string> SelectParser::parseTouple() {
	vector<string> touples;

	throwOnEOF();

	if ((*iterator)->isDiamondOpenBrace()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a '<', but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isName()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a name, but instead got: " + (*iterator)->toString());
	}

	while ((*iterator)->isName()) {
		touples.push_back((*iterator)->getValue());
		nextElement();
		throwOnEOF();

		if ((*iterator)->isComma()) {
			nextElement();
			throwOnEOF();
			continue;
		} else {
			break;
		}
	}

	if ((*iterator)->isDiamondCloseBrace()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a '>', but instead got: " + (*iterator)->toString());
	}
//	nextElement(); -- don't uncomment it. I left it here, to mark that you can't invoke nextElement() here

	return touples;
}
