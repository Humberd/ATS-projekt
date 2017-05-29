#pragma once
#include <vector>
#include "DeclaredVariable.h"
#include "QueryRequest.h"

using namespace std;

class QueryVariablesValidator {
public:
	explicit QueryVariablesValidator();
	~QueryVariablesValidator();

	void validate(vector<DeclaredVariable*> declaredVariables,
	              QueryRequest* queryRequest) const;

	void checkIfVariablesWereDeclared(vector<DeclaredVariable*> declaredVariables,
	                                  QueryRequest* queryRequest) const;
	bool doesVariableExist(string varName, vector<DeclaredVariable*> declaredVariables) const;

	void checkIfVariablesHaveValidProperties(vector<DeclaredVariable*> declaredVariables,
	                                         QueryRequest* queryRequest) const;
	bool doesPropertyExistOnType(string propertyName, string type) const;
	string getVariableType(string varName, vector<DeclaredVariable*> declaredVariables) const;

	void addTypesToVariablesAndParams(vector<DeclaredVariable*> declaredVariables,
	                                  QueryRequest* queryRequest) const;
};
