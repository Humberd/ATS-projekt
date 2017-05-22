#include "WithParser.h"
#include "QParsersRepository.h"
#include "QParserException.h"

WithParser::WithParser(QParsersRepository* parsersRepo,
                       vector<QLexerToken*>::iterator& lexerToken,
                       vector<QLexerToken*>::iterator& iteratorEnd) : QParsingEntity(parsersRepo, lexerToken, iteratorEnd) {
}

WithParser::~WithParser() {
}

WithRequest* WithParser::parse() const {
	WithRequest* withRequest = new WithRequest;

	throwOnEOF();

	QueryVariable* leftSide = parsersRepo->variableParser->parse();
	if (leftSide->getPropertyName().empty()) {
		throw QParserException(getClassName() + " - left side variable " + leftSide->getName() + " need to have a proprtyName");
	}
	withRequest->setLeftSideVariable(leftSide);
	nextElement();
	throwOnEOF();

	if ((*iterator)->isEquals()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected equals sign '=', but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isInteger()) {
		withRequest->setType(WithType::INTEGER);
		withRequest->setRightSideInteger(stoi((*iterator)->getValue()));
	} else if ((*iterator)->isName()) {
		auto rightSide = parsersRepo->variableParser->parse();
		if (rightSide->getPropertyName().empty()) {
			throw QParserException(getClassName() + " - right side variable " + rightSide->getName() + " need to have a proprtyName");
		}
		withRequest->setType(WithType::VARIABLE);
		withRequest->setRightSideVariable(rightSide);
	} else if ((*iterator)->isQuotationMark()) {
		withRequest->setType(WithType::STRING);
		withRequest->setRightSideString(parsersRepo->methodParser->parseString());
	}
	nextElement();

	return withRequest;
}
