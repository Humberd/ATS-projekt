#include "ReturnRequest.h"

ReturnRequest::ReturnRequest() {
}

ReturnRequest::~ReturnRequest() {
	for (auto variable : variables) {
		delete variable;
	}
	variables.clear();
}

ReturnType ReturnRequest::getReturnType() const {
	return returnType;
}

void ReturnRequest::setReturnType(const ReturnType returnType) {
	this->returnType = returnType;
}

vector<QueryVariable*> ReturnRequest::getVariables() const {
	return variables;
}

void ReturnRequest::setVariables(const vector<QueryVariable*> queryVariables) {
	variables = queryVariables;
}


