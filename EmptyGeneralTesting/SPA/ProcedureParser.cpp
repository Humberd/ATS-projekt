#include "ProcedureParser.h"
#include "ParserException.h"
#include "ProcedureNode.h"
#include "ParsersRepository.h"

ProcedureParser::ProcedureParser(ParsersRepository* parsersRepo,
                                 vector<LexerToken*>::iterator& iterator,
                                 vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

ProcedureParser::~ProcedureParser() {
}

Node* ProcedureParser::parse() {
	Node* procNode;

	throwOnEOF();

	if ((*iterator)->isProcedure()) {
		//do nothing
	} else {
		throw ParserException(getClassName() + " - expected a 'procedure' keyword, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isName()) {
		procNode = new ProcedureNode((*iterator)->getFileLineNumber(), (*iterator)->getValue());
	} else {
		throw ParserException(getClassName() + " - expected a name, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	Node* statementListNode = parsersRepo->statementListParser->parse();

	if (statementListNode == nullptr) {
		throw ParserException(getClassName() + " - unexxpected statementList node == nullptr");
	}

	procNode->addChild(statementListNode);

	return procNode;
}
