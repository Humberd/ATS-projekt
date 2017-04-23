#include "IfParser.h"
#include "ParsersRepository.h"
#include "ParserException.h"
#include "IfNode.h"
#include "VariableNode.h"

IfParser::IfParser(ParsersRepository* parsersRepo,
                   vector<LexerToken*>::iterator& iterator,
                   vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

IfParser::~IfParser() {
}

Node* IfParser::parse() {
	Node* leftExpr;
	Node* midExpr;
	Node* rightExpr;
	Node* ifNode;

	throwOnEOF();

	if ((*iterator)->isIf()) {
		ifNode = new IfNode((*iterator)->getFileLineNumber());
	} else {
		throw ParserException(getClassName() + " - expected an 'if' keyword, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isName()) {
		leftExpr = new VariableNode((*iterator)->getFileLineNumber(), (*iterator)->getValue());
	} else {
		throw ParserException(getClassName() + " - expected a name, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	midExpr = parsersRepo->statementListParser->parse();
	if (midExpr == nullptr) {
		throw ParserException(getClassName() + " - unexpected first statementList == nullptr");
	}

	if ((*iterator)->isElse()) {
		//do nothing
	} else {
		throw ParserException(getClassName() + " - expected an 'else' keyword, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	rightExpr = parsersRepo->statementListParser->parse();
	if (rightExpr == nullptr) {
		throw ParserException(getClassName() + " - unexpected second statementList == nullptr");
	}

	ifNode->addChild(leftExpr);
	ifNode->addChild(midExpr);
	ifNode->addChild(rightExpr);

	return ifNode;
}
