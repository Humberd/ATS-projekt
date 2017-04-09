#include "ASTException.h"
#include <string>

ASTException::ASTException(Node* node, char const* _Message) : exception(_Message) {
	this->node = node;
}

ASTException::ASTException(Node* node, string& _Message) : exception(_Message.c_str()) {
	this->node = node;
}

ASTException::ASTException(Node* node, string const& _Message): exception(_Message.c_str()) {
	this->node = node;
}

string ASTException::errorMessage() const {
	return string(typeid(*this->node).name()) + " at line: " + to_string(this->node->getLineNumber()) + " - ";
}

char const* ASTException::what() const {
	return (this->errorMessage() + exception::what()).c_str();
}
