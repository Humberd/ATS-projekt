#include "CallParser.h"
#include "ParsersRepository.h"
#include "ParserException.h"
#include "CallNode.h"

CallParser::CallParser(ParsersRepository* parsersRepo,
                       vector<LexerToken*>::iterator& iterator,
                       vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

CallParser::~CallParser() {
}

Node* CallParser::parse() {
	Node* callNode;

	throwOnEOF();

	if ((*iterator)->isCall()) {
		//empty
	} else {
		throw ParserException(getClassName() + " - expected a 'call' keyword, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isName()) {
		callNode = new CallNode((*iterator)->getFileLineNumber(), (*iterator)->getValue());
	} else {
		throw ParserException(getClassName() + " - expected a name, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isSemicolon()) {
		//empty
	} else {
		throw ParserException(getClassName() + " - expected a semicolon, but instead got: " + (*iterator)->toString());
	}
	nextElement();

	return callNode;
}
