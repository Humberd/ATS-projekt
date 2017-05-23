#include "QueryRequest.h"

QueryRequest::QueryRequest() {
}

QueryRequest::~QueryRequest() {
	delete returnRequest;
	for (auto methodRequest : methodRequests) {
		delete methodRequest;
	}
	methodRequests.clear();

	for (auto withRequest : withRequests) {
		delete withRequest;
	}
	withRequests.clear();

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

vector<WithRequest*> QueryRequest::getWithRequests() const {
	return withRequests;
}

void QueryRequest::setWithRequests(const vector<WithRequest*> withRequests) {
	this->withRequests = withRequests;
}
