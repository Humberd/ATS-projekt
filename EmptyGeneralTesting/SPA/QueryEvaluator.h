#pragma once
#include <vector>
#include "EvalUnit.h"
#include "DeclaredVariable.h"
#include "PkbBridge.h"
#include "QueryRequest.h"

class QueryRequest;
using namespace std;

class QueryEvaluator {
private:
	vector<vector<EvalUnit*>*> evalResults;
	vector<string> columnVariableNames;

	vector<DeclaredVariable*> declaredVariables;
	QueryRequest* queryRequest;

	PkbBrigde* pkbBrigde;

public:
	explicit QueryEvaluator(vector<DeclaredVariable*> declaredVariables,
	                        QueryRequest* queryRequest);
	~QueryEvaluator();

	void evaluate();

	void evaluateMethod(MethodRequest* methodRequest);
	void evaluateParent(MethodRequest* parentRequest);

};
