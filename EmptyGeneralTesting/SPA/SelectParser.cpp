#include "SelectParser.h"
#include "QParserException.h"
#include "QParsersRepository.h";

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

			nextElement();
		} else if ((*iterator)->isSpecialCharacter()) {
			returnRequest->setReturnType(ReturnType::VARIABLES);
			returnRequest->setVariables(parseTouple());
		} else if((*iterator)->isName()) {
			returnRequest->setReturnType(ReturnType::VARIABLES);
			returnRequest->setVariables(parseVariable());
		}

	return returnRequest;
}


vector<QueryVariable*> SelectParser::parseVariable() {
	vector<QueryVariable*> touples;
	touples.push_back(parsersRepo->variableParser->parse());

	return touples;
}

vector<QueryVariable*> SelectParser::parseTouple() {
	vector<QueryVariable*> touples;

	throwOnEOF();

	if ((*iterator)->isDiamondOpenBrace()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a '<', but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	while (iterator != iteratorEnd &&
		(*iterator)->isName()) {
		touples.push_back(parsersRepo->variableParser->parse());

		if ((*iterator)->isComma()) {
			nextElement();
			throwOnEOF();
		} else {
			break;
		}
	}

	if ((*iterator)->isDiamondCloseBrace()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a '>', but instead got: " + (*iterator)->toString());
	}
	nextElement();

	return touples;
}
