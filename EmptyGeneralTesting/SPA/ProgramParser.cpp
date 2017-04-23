#include "ProgramParser.h"
#include "ParsersRepository.h"
#include "ProgramNode.h"
#include "ParserException.h"

ProgramParser::ProgramParser(ParsersRepository* parsersRepo,
                             vector<LexerToken*>::iterator& iterator,
                             vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

ProgramParser::~ProgramParser() {
}

Node* ProgramParser::parse() {
	throwOnEOF();

	Node* programNode = new ProgramNode((*iterator)->getFileLineNumber());

	while (iterator != iteratorEnd) {
		Node* procedureNode = parsersRepo->procedureParser->parse();

		if (procedureNode == nullptr) {
			throw ParserException(getClassName() + " - unexpected procedureNode == nullptr");
		}

		programNode->addChild(procedureNode);
	}

	return programNode;
}
