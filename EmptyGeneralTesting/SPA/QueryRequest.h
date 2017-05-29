#pragma once
#include <vector>
#include "MethodRequest.h"
#include "ReturnRequest.h"
#include "WithRequest.h"

using namespace std;

class QueryRequest {
private:
	ReturnRequest* returnRequest;
	vector<MethodRequest*> methodRequests;
	vector<WithRequest*> withRequests;

public:
	explicit QueryRequest();
	~QueryRequest();

	ReturnRequest* getReturnRequest() const;
	void setReturnRequest(ReturnRequest* const returnRequest);
	vector<MethodRequest*> getMethodRequests() const;
	void setMethodRequests(const vector<MethodRequest*> methodRequests);
	vector<WithRequest*> getWithRequests() const;
	void setWithRequests(const vector<WithRequest*> withRequests);
};
