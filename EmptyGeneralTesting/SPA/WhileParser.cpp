#include "WhileParser.h"
#include "ParsersRepository.h"
#include "ParserException.h"
#include "WhileNode.h"
#include "VariableNode.h"

WhileParser::WhileParser(ParsersRepository* parsersRepo,
                         vector<LexerToken*>::iterator& iterator,
                         vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

WhileParser::~WhileParser() {
}

Node* WhileParser::parse() {
	Node* leftExpr;
	Node* whileNode;

	throwOnEOF();

	if ((*iterator)->isWhile()) {
		whileNode = new WhileNode((*iterator)->getSourceLineNumber());
	} else {
		throw ParserException(getClassName() + " - expected a 'while' keyword, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isName()) {
		leftExpr = new VariableNode((*iterator)->getSourceLineNumber(), (*iterator)->getValue());
	} else {
		throw ParserException(getClassName() + " - expected a name, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	Node* rightExpr = parsersRepo->statementListParser->parse();

	if (rightExpr == nullptr) {
		throw ParserException(getClassName() + " - unexpected statement list == nullptr");
	}

	whileNode->addChild(leftExpr);
	whileNode->addChild(rightExpr);

	return whileNode;
}
