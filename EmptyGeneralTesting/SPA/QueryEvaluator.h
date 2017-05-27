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
	bool booleanResult;
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

	MethodEvaluatorResponse* evaluateMethod(string methodName, InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep);
	MethodEvaluatorResponse* parentEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep);

	void changeResultsStateBasedOnResponses(vector<MethodEvaluatorResponse*>& responses,
	                                        vector<vector<string>*>& oldState,
	                                        vector<vector<string>*>& newState,
	                                        bool& booleanResult,
	                                        vector<string>& columnVariableNames);
	void changeVectorResultsBasedOnResponses(MethodEvaluatorResponse* response,
	                                         vector<vector<string>*>& oldState,
	                                         vector<vector<string>*>& newState,
	                                         int insertToColumnIdex);


	InvokationParam* changeParameterToInvokationParam(Parameter* parameter);

	vector<InvokationParam*> generateParamsIncaseOfAvailableResults(InvokationParam* invokationParam);

	int findIndexOfColumnVariableName(string varName);
	int findIndexOfColumnVariableName(string varName, vector<string>& arr);
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
	bool getBooleanResult() const;
	void setBooleanResult(const bool booleanResult);
};
