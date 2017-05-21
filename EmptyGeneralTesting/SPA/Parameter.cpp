#include "Parameter.h"

Parameter::Parameter(ParameterType type, string stringValue) : type(type),
                                                               stringValue(stringValue),
                                                               integerValue(0) {
}

Parameter::Parameter(ParameterType type, int integerValue) : type(type),
                                                             stringValue(""),
                                                             integerValue(integerValue) {
}


Parameter::Parameter(ParameterType type) : type(type),
                                           stringValue(""),
                                           integerValue(0) {
}

Parameter::~Parameter() {
}

ParameterType Parameter::getType() const {
	return type;
}

void Parameter::setType(const ParameterType type) {
	this->type = type;
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
