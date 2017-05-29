#include "MethodParser.h"
#include "QParserException.h"
#include "QParsersRepository.h";


MethodParser::MethodParser(QParsersRepository* parsersRepo,
                           vector<QLexerToken*>::iterator& lexerToken,
                           vector<QLexerToken*>::iterator& iteratorEnd) : QParsingEntity(parsersRepo, lexerToken, iteratorEnd) {
}

MethodParser::~MethodParser() {
}

MethodRequest* MethodParser::parse() const {
	MethodRequest* methodRequest = new MethodRequest;

	throwOnEOF();

	if ((*iterator)->isQueryMethod()) {
		methodRequest->setMethodName((*iterator)->getValue());
	} else {
		throw QParserException(getClassName() + " - expected a method name, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isStar()) {
		methodRequest->setGoDeep(true);
		nextElement();
	} else {
		methodRequest->setGoDeep(false);
	}
	throwOnEOF();

	if ((*iterator)->isOpenBrace()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected an open brace '(', but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	methodRequest->setLeftParam(parseParameter());
	nextElement();
	throwOnEOF();

	if ((*iterator)->isComma()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a comma ',', but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	methodRequest->setRightParam(parseParameter());
	nextElement();
	throwOnEOF();

	if ((*iterator)->isCloseBrace()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a close brace ')', but instead got: " + (*iterator)->toString());
	}
	nextElement();

	return methodRequest;
}


Parameter* MethodParser::parseParameter() const {
	Parameter* parameter = new Parameter;

	throwOnEOF();

	if ((*iterator)->isInteger()) {
		parameter->setType(ParameterType::INTEGER);
		parameter->setIntegerValue(stoi((*iterator)->getValue()));
	} else if ((*iterator)->isName()) {
		parameter->setType(ParameterType::VARIABLE);
		parameter->setVariableName((*iterator)->getValue());
	} else if ((*iterator)->isQuotationMark()) {
		parameter->setType(ParameterType::STRING);
		parameter->setStringValue(parseString());
	} else if ((*iterator)->isLowDash()) {
		parameter->setType(ParameterType::ANY);
	} else {
		throw QParserException(getClassName() + " - unexpected token in parseParameter()', but instead got: " + (*iterator)->toString());
	}

	return parameter;
}

/*
 * This method parses the following sequence (with quotation marks): "myCustomString"
 */
string MethodParser::parseString() const {
	string response;

	throwOnEOF();

	if ((*iterator)->isQuotationMark()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected an opening quotation mark '\"', but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isName()) {
		response = (*iterator)->getValue();
	} else {
		throw QParserException(getClassName() + " - expected a name, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isQuotationMark()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a closing quotation mark '\"', but instead got: " + (*iterator)->toString());
	}

	return response;
}
