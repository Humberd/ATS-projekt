#pragma once
#include <vector>
#include "DeclaredVariable.h"
#include "PkbBridge.h"
#include "QueryRequest.h"
#include "InvokationParam.h"
#include "MethodEvaluatorResponse.h"
#include "SpaDataContainer.h"
#include "StatementsFilter.h"

class QueryRequest;
using namespace std;

class QueryEvaluator {
private:
	vector<vector<string>*> evalResults;
	vector<bool> booleanResponses;
	vector<string> columnVariableNames;

	vector<DeclaredVariable*> declaredVariables;
	QueryRequest* queryRequest;

	PkbBrigde* pkbBrigde;
	SpaDataContainer* spaDataContainer;

public:
	explicit QueryEvaluator();
	explicit QueryEvaluator(vector<DeclaredVariable*> declaredVariables,
	                        QueryRequest* queryRequest,
	                        SpaDataContainer* spaDataContainer);
	~QueryEvaluator();

	void evaluate();
	vector<vector<string>> evaluateReturn();

	MethodEvaluatorResponse* evaluateMethod(string methodName, InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep);
	MethodEvaluatorResponse* parentEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep);
	MethodEvaluatorResponse* followsEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep);
	MethodEvaluatorResponse* modifiesEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep);
	MethodEvaluatorResponse* usesEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep);
	MethodEvaluatorResponse* callsEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep);
	MethodEvaluatorResponse* nextEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep);


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
	vector<InvokationParam*> generateParamsIncaseOfAvailableResults(InvokationParam* invokationParam, string method, int paramNumber);

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
	SpaDataContainer* getSpaDataContainer() const;
	void setSpaDataContainer(SpaDataContainer* const spaDataContainer);
	vector<bool> getBooleanResponses() const;
	void setBooleanResponses(const vector<bool> booleanResponses);
};
