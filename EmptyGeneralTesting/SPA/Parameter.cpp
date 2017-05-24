#include "Parameter.h"

Parameter::Parameter() {
}

Parameter::~Parameter() {
}

ParameterType Parameter::getType() const {
	return type;
}

void Parameter::setType(const ParameterType type) {
	this->type = type;
}

string Parameter::getVariableName() const {
	return variableName;
}

void Parameter::setVariableName(const string variableName) {
	this->variableName = variableName;
}

string Parameter::getVariableType() const {
	return variableType;
}

void Parameter::setVariableType(const string variableType) {
	this->variableType = variableType;
}

string Parameter::getStringValue() const {
	return stringValue;
}

void Parameter::setStringValue(const string stringValue) {
	this->stringValue = stringValue;
}

int Parameter::getIntegerValue() const {
	return integerValue;
}

void Parameter::setIntegerValue(const int integerValue) {
	this->integerValue = integerValue;
}
