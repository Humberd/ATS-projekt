#include "InvokationParam.h"

InvokationParam::InvokationParam() {
}

InvokationParam::~InvokationParam() {
}

string InvokationParam::getValue() const {
	return value;
}

void InvokationParam::setValue(const string value) {
	this->value = value;
}

ValueType InvokationParam::getValueType() const {
	return valueType;
}

void InvokationParam::setValueType(const ValueType valueType) {
	this->valueType = valueType;
}

InvokationParamState InvokationParam::getState() const {
	return state;
}

void InvokationParam::setState(const InvokationParamState state) {
	this->state = state;
}

string InvokationParam::getVariableName() const {
	return variableName;
}

void InvokationParam::setVariableName(const string variableName) {
	this->variableName = variableName;
}

string InvokationParam::getVariableType() const {
	return variableType;
}

void InvokationParam::setVariableType(const string variableType) {
	this->variableType = variableType;
}

InvokationParam* InvokationParam::copy() const {
	InvokationParam* copiedInstance = new InvokationParam;
	copiedInstance->setVariableName(this->getVariableName());
	copiedInstance->setState(this->getState());
	copiedInstance->setValue(this->getValue());
	copiedInstance->setValueType(this->valueType);
	return copiedInstance;
}


string InvokationParam::toString() const {
	return "InvokationParam {"
			" value=" + value +
			" variableName=" + variableName +
			"}";
}
