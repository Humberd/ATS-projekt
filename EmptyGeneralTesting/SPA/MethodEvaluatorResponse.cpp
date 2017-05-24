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

