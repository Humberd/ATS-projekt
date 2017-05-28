#include "MethodEvaluatorResponse.h"

MethodEvaluatorResponse::MethodEvaluatorResponse() {
}

MethodEvaluatorResponse::~MethodEvaluatorResponse() {
}

ResponseState MethodEvaluatorResponse::getState() const {
	return state;
}

void MethodEvaluatorResponse::setState(const ResponseState state) {
	this->state = state;
}

vector<string> MethodEvaluatorResponse::getVectorResponse() const {
	return vectorResponse;
}

void MethodEvaluatorResponse::setVectorResponse(const vector<string> basicStrings) {
	vectorResponse = basicStrings;
}

bool MethodEvaluatorResponse::getBooleanResponse() const {
	return booleanResponse;
}

void MethodEvaluatorResponse::setBooleanResponse(const bool booleanResponse) {
	this->booleanResponse = booleanResponse;
}

string MethodEvaluatorResponse::getVariableName() const {
	return variableName;
}

void MethodEvaluatorResponse::setVariableName(const string variableName) {
	this->variableName = variableName;
}

string MethodEvaluatorResponse::getVariableType() const {
	return variableType;
}

void MethodEvaluatorResponse::setVariableType(const string variableType) {
	this->variableType = variableType;
}

string MethodEvaluatorResponse::getInsertToColumnName() const {
	return insertToColumnName;
}

void MethodEvaluatorResponse::setInsertToColumnName(const string insertToColumnName) {
	this->insertToColumnName = insertToColumnName;
}

string MethodEvaluatorResponse::getInsertToColumnValue() const {
	return insertToColumnValue;
}

void MethodEvaluatorResponse::setInsertToColumnValue(const string insertToColumnValue) {
	this->insertToColumnValue = insertToColumnValue;
}

