#include "EvalUnit.h"

EvalUnit::EvalUnit() {
}

EvalUnit::~EvalUnit() {
}

EvalUnitType EvalUnit::getType() const {
	return type;
}

void EvalUnit::setType(const EvalUnitType type) {
	this->type = type;
}

int EvalUnit::getIntegerValue() const {
	return integerValue;
}

void EvalUnit::setIntegerValue(const int integerValue) {
	this->integerValue = integerValue;
}

string EvalUnit::getStringValue() const {
	return stringValue;
}

void EvalUnit::setStringValue(const string stringValue) {
	this->stringValue = stringValue;
}

string EvalUnit::getVariableName() const {
	return variableName;
}

void EvalUnit::setVariableName(const string variableName) {
	this->variableName = variableName;
}
