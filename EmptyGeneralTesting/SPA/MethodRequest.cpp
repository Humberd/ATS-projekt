#include "MethodRequest.h"

MethodRequest::MethodRequest() {
}

MethodRequest::~MethodRequest() {
}

string MethodRequest::getMethodName() const {
	return methodName;
}

void MethodRequest::setMethodName(const string methodName) {
	this->methodName = methodName;
}

bool MethodRequest::getGoDeep() const {
	return goDeep;
}

void MethodRequest::setGoDeep(const bool goDeep) {
	this->goDeep = goDeep;
}

Parameter* MethodRequest::getLeftParam() const {
	return leftParam;
}

void MethodRequest::setLeftParam(Parameter* const leftParam) {
	this->leftParam = leftParam;
}

Parameter* MethodRequest::getRightParam() const {
	return rightParam;
}

void MethodRequest::setRightParam(Parameter* const rightParam) {
	this->rightParam = rightParam;
}
