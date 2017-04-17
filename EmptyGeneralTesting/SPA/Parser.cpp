#include "Parser.h"
#include "ProgramNode.h"
#include "ParserException.h"
#include "CallNode.h"

Parser::Parser() {
}

Parser::~Parser() {
}

Node* Parser::parse(vector<LexerToken*>& tokensList) {
	auto iterator = tokensList.begin();
	auto iteratorEnd = tokensList.end();

	return nullptr;
}

Node* Parser::parseCall(vector<LexerToken*>::iterator& iterator,
                        vector<LexerToken*>::iterator& iteratorEnd) {
	CallNode* node = nullptr;
	int fileLineNumber;
	string procedureName;

	if ((*iterator)->isCall()) {
		fileLineNumber = (*iterator)->getFileLineNumber();
	} else {
		throw ParserException("parseCall - Expected a call keyword, but instead got: " + (*iterator)->toString());
	}

	if (iterator != iteratorEnd) {
		++iterator;
	} else {
		throw ParserException("parseCall - Expected a name, but instead got end of file");
	}

	if ((*iterator)->isName()) {
		if ((*iterator)->getFileLineNumber() == fileLineNumber) {
			procedureName = (*iterator)->getValue();
		} else {
			throw ParserException("parseCall - Expected a name to be at the same line as a call keyword, but instead got: " + (*iterator)->toString());
		}
	} else {
		throw ParserException("parseCall - Expected a name, but instead got: " + (*iterator)->toString());
	}

	if (iterator != iteratorEnd) {
		++iterator;
	} else {
		throw ParserException("parseCall - Expected a name, but instead got end of file");
	}

	if ((*iterator)->isSemicolon()) {
		if ((*iterator)->getFileLineNumber() == fileLineNumber) {
			node = new CallNode(fileLineNumber, procedureName);
		} else {
			throw ParserException("parseCall - Expected a semicolon to be at the same line as a call keyword, but instead got: " + (*iterator)->toString());
		}
	} else {
		throw ParserException("parseCall - Expected a semicolon, but  instead got: " + (*iterator)->toString());
	}

	return node;
}


Node* Parser::parseCallBetter(vector<LexerToken*>::iterator& iterator,
                              vector<LexerToken*>::iterator& iteratorEnd) {
	vector<bool (LexerToken::*)() const> methodsList;
	methodsList.push_back(&LexerToken::isCall);
	methodsList.push_back(&LexerToken::isName);
	methodsList.push_back(&LexerToken::isSemicolon);

	CallNode* node = nullptr;
	int fileLineNumber;
	string procedureName;

	for (auto method : methodsList) {
		if (!((*iterator) ->* method)()) {
			throw ParserException("parseCall - got: " + (*iterator)->toString());

		} 

		if (iterator != iteratorEnd) {
			++iterator;
		} else {
			throw ParserException("parseCall - got end of file");
		}
	}



	return node;
}
