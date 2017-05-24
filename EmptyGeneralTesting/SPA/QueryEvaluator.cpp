#include "QueryEvaluator.h"
#include "QueryEvaluatorException.h"
#include <algorithm>

QueryEvaluator::QueryEvaluator(vector<DeclaredVariable*> declaredVariables,
                               QueryRequest* queryRequest): declaredVariables(declaredVariables), queryRequest(queryRequest) {
	pkbBrigde = new PkbBrigde;
}

QueryEvaluator::~QueryEvaluator() {
	for (auto result : evalResults) {
		result->clear();
		delete result;
	}
	evalResults.clear();
	columnVariableNames.clear();

	delete pkbBrigde;
}

void QueryEvaluator::evaluate() {
}

InvokationParam* QueryEvaluator::changeParameterToInvokationParam(Parameter* parameter) {
	InvokationParam* invokationParam = new InvokationParam;

	/*Param is type ANY (_)*/
	if (parameter->getType() == ParameterType::ANY) {
		invokationParam->setState(InvokationParamState::ANY);
		return invokationParam;
	}

	if (parameter->getType() == ParameterType::VARIABLE) {
		invokationParam->setState(InvokationParamState::VARIABLE);
		invokationParam->setVariableName(parameter->getVariableName());
		return invokationParam;
	}

	if (parameter->getType() == ParameterType::INTEGER) {
		invokationParam->setState(InvokationParamState::VALUE);
		invokationParam->setValueType(ValueType::INTEGER);
		invokationParam->setValue(to_string(parameter->getIntegerValue()));
		return invokationParam;
	}

	if (parameter->getType() == ParameterType::STRING) {
		invokationParam->setState(InvokationParamState::VALUE);
		invokationParam->setValueType(ValueType::STRING);
		invokationParam->setValue(parameter->getStringValue());
		return invokationParam;
	}

	throw QueryEvaluatorException("changeParameterToInvokationParam() - didn't pass a type check");
}

vector<InvokationParam*> QueryEvaluator::generateParamsIncaseOfAvailableResults(InvokationParam* invokationParam) {
	vector<InvokationParam*> params;

	if (invokationParam->getState() == InvokationParamState::VALUE) {
		params.push_back(invokationParam);
		return params;
	}

	if (invokationParam->getState() == InvokationParamState::ANY) {
		throw QueryEvaluatorException("Unsupported param exception: '_'");
	}

	if (invokationParam->getState() == InvokationParamState::VARIABLE) {
		int indexOfColumnVariable = findIndexOfColumnVariableName(invokationParam->getVariableName());
		if (indexOfColumnVariable < 0) {
			params.push_back(invokationParam);
			return params;
		}

//		evalResults.at(indexOfColumnVariable);
	}

	throw QueryEvaluatorException("generateParamsIncaseOfAvailableResults() shouldn't reach end of the function");
}


int QueryEvaluator::findIndexOfColumnVariableName(string varName) {
	for (int i = 0; i < columnVariableNames.size(); i++) {
		if (columnVariableNames.at(i) == varName) {
			return i;
		}
	}

	return -1;
}


vector<string> QueryEvaluator::findUniqueEvalResultsFromColumn(int columnIndex) {
	vector<string> uniqueResults;

	for (vector<string>* row : evalResults) {
		uniqueResults.push_back(row->at(columnIndex));
	}

	sort(uniqueResults.begin(), uniqueResults.end());
	uniqueResults.erase(unique(uniqueResults.begin(), uniqueResults.end()), uniqueResults.end());

	return uniqueResults;
}


/*--------------------------------------------------------------------*/
vector<vector<string>*> QueryEvaluator::getEvalResults() const {
	return evalResults;
}

void QueryEvaluator::setEvalResults(const vector<vector<string>*> basicStringses) {
	evalResults = basicStringses;
}

vector<string> QueryEvaluator::getColumnVariableNames() const {
	return columnVariableNames;
}

void QueryEvaluator::setColumnVariableNames(const vector<string> columnVariableNames) {
	this->columnVariableNames = columnVariableNames;
}

vector<DeclaredVariable*> QueryEvaluator::getDeclaredVariables() const {
	return declaredVariables;
}

void QueryEvaluator::setDeclaredVariables(const vector<DeclaredVariable*> declaredVariables) {
	this->declaredVariables = declaredVariables;
}

QueryRequest* QueryEvaluator::getQueryRequest() const {
	return queryRequest;
}

void QueryEvaluator::setQueryRequest(QueryRequest* const queryRequest) {
	this->queryRequest = queryRequest;
}

PkbBrigde* QueryEvaluator::getPkbBrigde() const {
	return pkbBrigde;
}

void QueryEvaluator::setPkbBrigde(PkbBrigde* const pkbBrigde) {
	this->pkbBrigde = pkbBrigde;
}
