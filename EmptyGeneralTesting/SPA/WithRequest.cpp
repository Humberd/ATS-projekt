#include "WithRequest.h"

WithRequest::WithRequest() {
}

WithRequest::~WithRequest() {
}

WithType WithRequest::getType() const {
	return type;
}

void WithRequest::setType(const WithType type) {
	this->type = type;
}

QueryVariable* WithRequest::getLeftSideVariable() const {
	return leftSideVariable;
}

void WithRequest::setLeftSideVariable(QueryVariable* const leftSideVariable) {
	this->leftSideVariable = leftSideVariable;
}

QueryVariable* WithRequest::getRightSideVariable() const {
	return rightSideVariable;
}

void WithRequest::setRightSideVariable(QueryVariable* const rightSideVariable) {
	this->rightSideVariable = rightSideVariable;
}

int WithRequest::getRightSideInteger() const {
	return rightSideInteger;
}

void WithRequest::setRightSideInteger(const int rightSideInteger) {
	this->rightSideInteger = rightSideInteger;
}

string WithRequest::getRightSideString() const {
	return rightSideString;
}

void WithRequest::setRightSideString(const string rightSideString) {
	this->rightSideString = rightSideString;
}
