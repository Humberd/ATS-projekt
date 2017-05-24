#pragma once
#include <vector>
#include "DeclaredVariable.h"
#include "PkbBridge.h"
#include "QueryRequest.h"
#include "InvokationParam.h"

class QueryRequest;
using namespace std;

class QueryEvaluator {
private:
	vector<vector<string>*> evalResults;
	vector<string> columnVariableNames;

	vector<DeclaredVariable*> declaredVariables;
	QueryRequest* queryRequest;

	PkbBrigde* pkbBrigde;

public:
	explicit QueryEvaluator(vector<DeclaredVariable*> declaredVariables,
	                        QueryRequest* queryRequest);
	~QueryEvaluator();

	void evaluate();

	InvokationParam* changeParameterToInvokationParam(Parameter* parameter);

};
