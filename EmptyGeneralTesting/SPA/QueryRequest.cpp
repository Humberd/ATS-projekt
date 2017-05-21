#include "QueryRequest.h"

QueryRequest::QueryRequest() {
}

QueryRequest::~QueryRequest() {
}

ReturnRequest* QueryRequest::getReturnRequest() const {
	return returnRequest;
}

void QueryRequest::setReturnRequest(ReturnRequest* const returnRequest) {
	this->returnRequest = returnRequest;
}

vector<MethodRequest*> QueryRequest::getMethodRequests() const {
	return methodRequests;
}

void QueryRequest::setMethodRequests(const vector<MethodRequest*> methodRequests) {
	this->methodRequests = methodRequests;
}

