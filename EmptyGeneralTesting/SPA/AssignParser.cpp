#include "AssignParser.h"
#include "ParserException.h"
#include "AssignNode.h"
#include "VariableNode.h"
#include "ParsersRepository.h"

AssignParser::AssignParser(ParsersRepository* parsersRepo,
                           vector<LexerToken*>::iterator& iterator,
                           vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

AssignParser::~AssignParser() {
}

Node* AssignParser::parse() {
	Node* leftExpr;
	Node* assignNode;

	throwOnEOF();

	if ((*iterator)->isName()) {
		leftExpr = new VariableNode((*iterator)->getFileLineNumber(), (*iterator)->getValue());
		assignNode = new AssignNode((*iterator)->getFileLineNumber());
	} else {
		throw ParserException(getClassName() + " - expected a name, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isEquals()) {
		//empty
	} else {
		throw ParserException(getClassName() + " - expected an equals sign, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	/*Calling Expression Parser*/
	Node* rightExpr = parsersRepo->expressionParser->parse();

	assignNode->addChild(leftExpr);
	assignNode->addChild(rightExpr);

	return assignNode;
}
