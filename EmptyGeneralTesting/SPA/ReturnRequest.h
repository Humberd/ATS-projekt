#pragma once
#include "ReturnType.h"
#include <vector>
#include "QueryVariable.h"

using namespace std;

class ReturnRequest {
private:
	ReturnType returnType;
	vector<QueryVariable*> variables;

public:
	explicit ReturnRequest();
	~ReturnRequest();

	ReturnType getReturnType() const;
	void setReturnType(const ReturnType returnType);
	vector<QueryVariable*> getVariables() const;
	void setVariables(const vector<QueryVariable*> queryVariables);
};
