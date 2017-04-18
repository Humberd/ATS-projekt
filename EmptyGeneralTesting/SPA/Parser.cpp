#include "Parser.h"
#include "ProgramNode.h"
#include "ParserException.h"
#include "CallNode.h"
#include "AssignNode.h"
#include "VariableNode.h"

Parser::Parser() {
}

Parser::~Parser() {
}

Node* Parser::parse(vector<LexerToken*>& tokensList) {
	auto iterator = tokensList.begin();
	auto iteratorEnd = tokensList.end();

	return nullptr;
}


void Parser::nextElement(string name,
                         vector<LexerToken*>::iterator& iterator) {
	try {
		++iterator;
	} catch (exception& e) {
		throw ParserException(name + " - Unexpected end of file");
	}
}

Node* Parser::parseCall(vector<LexerToken*>::iterator& iterator) {
	CallNode* node = nullptr;
	int fileLineNumber;
	string procedureName;

	/*[call] Foo ;*/
	if ((*iterator)->isCall()) {
		fileLineNumber = (*iterator)->getFileLineNumber();
	} else {
		throw ParserException("parseCall - Expected a call keyword, but instead got: " + (*iterator)->toString());
	}

	nextElement(__FUNCDNAME__, iterator);

	/*call [Foo] ;*/
	if ((*iterator)->isName()) {
		if ((*iterator)->getFileLineNumber() == fileLineNumber) {
			procedureName = (*iterator)->getValue();
		} else {
			throw ParserException("parseCall - Expected a name to be at the same line as a call keyword, but instead got: " + (*iterator)->toString());
		}
	} else {
		throw ParserException("parseCall - Expected a name, but instead got: " + (*iterator)->toString());
	}

	nextElement(__FUNCDNAME__, iterator);

	/*call Foo [;]*/
	if ((*iterator)->isSemicolon()) {
		if ((*iterator)->getFileLineNumber() == fileLineNumber) {
			node = new CallNode(fileLineNumber, procedureName);
		} else {
			throw ParserException("parseCall - Expected a semicolon to be at the same line as a call keyword, but instead got: " + (*iterator)->toString());
		}
	} else {
		throw ParserException("parseCall - Expected a semicolon, but  instead got: " + (*iterator)->toString());
	}

	nextElement(__FUNCDNAME__, iterator);

	return node;
}

Node* Parser::parseAssign(vector<LexerToken*>::iterator& iterator) {
	AssignNode* node = nullptr;
	int fileLineNumber;
	string leftVariableName;

	/*[x] = <expr>*/
	if ((*iterator)->isName()) {
		fileLineNumber = (*iterator)->getFileLineNumber();
		leftVariableName = (*iterator)->getValue();
	} else {
		throw ParserException("assignCall - Expected a name variable, but instead got: " + (*iterator)->toString());
	}
	nextElement(__FUNCDNAME__, iterator);

	/*x [=] <expr>*/
	if ((*iterator)->isEquals()) {
		//do nothing
	} else {
		throw ParserException("assignCall - Expected an equals sign, but instead got: " + (*iterator)->toString());
	}
	nextElement(__FUNCDNAME__, iterator);

	/*x = [<expr>]*/
	Node* expressionNode = parseExpression(iterator);

	if ((*iterator)->isSemicolon()) {
		node = new AssignNode(fileLineNumber);
		node->addChild(new VariableNode(fileLineNumber, leftVariableName));
		node->addChild(expressionNode);
	} else {
		throw ParserException("assignCall - Expected a semicolon, but instead got: " + (*iterator)->toString());
	}
	nextElement(__FUNCDNAME__, iterator);

	return node;
}

Node* Parser::parseExpression(vector<LexerToken*>::iterator& iterator) {
	return nullptr;
}