#pragma once
#include <vector>
#include "DeclaredVariable.h"
#include "PkbBridge.h"
#include "QueryRequest.h"
#include "InvokationParam.h"
#include "MethodEvaluatorResponse.h"

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
	explicit QueryEvaluator();
	explicit QueryEvaluator(vector<DeclaredVariable*> declaredVariables,
	                        QueryRequest* queryRequest);
	~QueryEvaluator();

	void evaluate();

	void evaluateMethod(string methodName, InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep);
	MethodEvaluatorResponse* parentEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep);


	InvokationParam* changeParameterToInvokationParam(Parameter* parameter);

	vector<InvokationParam*> generateParamsIncaseOfAvailableResults(InvokationParam* invokationParam);

	int findIndexOfColumnVariableName(string varName);
	string findTypeOfDeclaredVariable(string varName);
	vector<string> findUniqueEvalResultsFromColumn(int columnIndex);


	/*-------------------------------------------------------*/
	vector<vector<string>*> getEvalResults() const;
	void setEvalResults(const vector<vector<string>*> basicStringses);
	vector<string> getColumnVariableNames() const;
	void setColumnVariableNames(const vector<string> columnVariableNames);
	vector<DeclaredVariable*> getDeclaredVariables() const;
	void setDeclaredVariables(const vector<DeclaredVariable*> declaredVariables);
	QueryRequest* getQueryRequest() const;
	void setQueryRequest(QueryRequest* const queryRequest);
	PkbBrigde* getPkbBrigde() const;
	void setPkbBrigde(PkbBrigde* const pkbBrigde);
};
