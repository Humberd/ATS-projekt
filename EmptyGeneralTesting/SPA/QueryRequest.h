#pragma once
#include <vector>
#include "MethodRequest.h"
#include "ReturnRequest.h"

using namespace std;

class QueryRequest {
private:
	ReturnRequest* returnRequest;
	vector<MethodRequest*> methodRequests;

public:
	explicit QueryRequest();
	~QueryRequest();


	ReturnRequest* getReturnRequest() const;
	void setReturnRequest(ReturnRequest* const returnRequest);
	vector<MethodRequest*> getMethodRequests() const;
	void setMethodRequests(const vector<MethodRequest*> methodRequests);
};
