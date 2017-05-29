#include "StatementListParser.h"
#include "ParsersRepository.h"
#include "StatementListNode.h"
#include "ParserException.h"
#include <sstream>

StatementListParser::StatementListParser(ParsersRepository* parsersRepo,
                                         vector<LexerToken*>::iterator& iterator,
                                         vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

StatementListParser::~StatementListParser() {
}

Node* StatementListParser::parse() {
	Node* statementListNode;

	throwOnEOF();

	if ((*iterator)->isOpenBrace()) {
		statementListNode = new StatementListNode((*iterator)->getSourceLineNumber());
	} else {
		throw ParserException(getClassName() + " - expected an open brace, but instead got: " + (*iterator)->toString());
	}
	nextElement();

	try {
		while (true) {
			vector<string> errorsList;
			throwOnEOF();

			if ((*iterator)->isCloseBrace()) {
				if (statementListNode->getChildren().size() != 0) {
					nextElement();
					break;
				} else {
					throw ParserException(getClassName() + " - there need to be at least one Statement: " + (*iterator)->toString());
				}
			}

			try {
				auto statementNode = parsersRepo->assignParser->parse();
				statementListNode->addChild(statementNode);
				continue;
			} catch (ParserException& e) {
				errorsList.push_back(e.what());
				errorsList.push_back("\n");
			}

			try {
				auto statementNode = parsersRepo->callParser->parse();
				statementListNode->addChild(statementNode);
				continue;
			} catch (ParserException& e) {
				errorsList.push_back(e.what());
				errorsList.push_back("\n");
			}

			try {
				auto statementNode = parsersRepo->whileParser->parse();
				statementListNode->addChild(statementNode);
				continue;
			} catch (ParserException& e) {
				errorsList.push_back(e.what());
				errorsList.push_back("\n");
			}

			try {
				auto statementNode = parsersRepo->ifParser->parse();
				statementListNode->addChild(statementNode);
				continue;
			} catch (ParserException& e) {
				errorsList.push_back(e.what());
				errorsList.push_back("\n");
			}

			string errorsString = "";
			for (auto error : errorsList) {
				errorsString += error;
			}

			throw ParserException(getClassName() + " - " + errorsString);
		}
	} catch (ParserException&) {
		delete statementListNode;
		throw;
	}

	return statementListNode;
}
