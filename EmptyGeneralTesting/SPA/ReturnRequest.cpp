#include "ReturnRequest.h"

ReturnRequest::ReturnRequest() {
}

ReturnRequest::~ReturnRequest() {
}

ReturnType ReturnRequest::getReturnType() const {
	return returnType;
}

void ReturnRequest::setReturnType(const ReturnType returnType) {
	this->returnType = returnType;
}

string ReturnRequest::getVariableName() const {
	return variableName;
}

void ReturnRequest::setVariableName(const string variableName) {
	this->variableName = variableName;
}

vector<string> ReturnRequest::getToupleVariableNames() const {
	return toupleVariableNames;
}

void ReturnRequest::setToupleVariableNames(const vector<string> toupleVariableNames) {
	this->toupleVariableNames = toupleVariableNames;
}

