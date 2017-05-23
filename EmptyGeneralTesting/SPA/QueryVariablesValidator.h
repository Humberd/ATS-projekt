#pragma once
#include <vector>
#include "DeclaredVariable.h"
#include "QueryRequest.h"

using namespace std;

class QueryVariablesValidator {
public:
	explicit QueryVariablesValidator();
	~QueryVariablesValidator();

	void validate(vector<DeclaredVariable*> variables,
	              QueryRequest* queryRequest) const;
};
