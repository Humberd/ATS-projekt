#include "QueryEvaluator.h"
#include "QueryEvaluatorException.h"
#include <algorithm>
#include "DeclarationKeywords.h"
#include "QueryMethods.h"

QueryEvaluator::QueryEvaluator() {
	pkbBrigde = nullptr;
}

QueryEvaluator::QueryEvaluator(vector<DeclaredVariable*> declaredVariables,
                               QueryRequest* queryRequest): declaredVariables(declaredVariables), queryRequest(queryRequest) {
	pkbBrigde = nullptr;
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
	for (auto methodRequest : queryRequest->getMethodRequests()) {
		InvokationParam* initialLeftParam = changeParameterToInvokationParam(methodRequest->getLeftParam());
		InvokationParam* initialRightParam = changeParameterToInvokationParam(methodRequest->getRightParam());

		auto leftParams = generateParamsIncaseOfAvailableResults(initialLeftParam);
		auto rightParams = generateParamsIncaseOfAvailableResults(initialRightParam);

		vector<MethodEvaluatorResponse*> responses;

		for (auto leftParam : leftParams) {
			for (auto rightParam: rightParams) {
				responses.push_back(evaluateMethod(methodRequest->getMethodName(), leftParam, rightParam, methodRequest->getGoDeep()));
			}
		}

		for (auto response : responses) {
			delete response;
		}
		responses.clear();
	}
}


MethodEvaluatorResponse* QueryEvaluator::evaluateMethod(string methodName, InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep) {
	MethodEvaluatorResponse* response = nullptr;
	if (methodName == QueryMethods::PARENT) {
		response = parentEvaluator(leftParam, rightParam, goDeep);
	} else {
		throw QueryEvaluatorException("evaluateMethod() - unsupported methodName: " + methodName);
	}

	return response;
}


void QueryEvaluator::changeResultsStateBasedOnResponses(vector<MethodEvaluatorResponse*>& responses,
                                                        vector<vector<string>*>& oldState,
                                                        vector<vector<string>*>& newState,
                                                        bool& booleanResult,
                                                        vector<string>& columnVariableNames) {
	for (auto response : responses) {
		if (response->getState() == ResponseState::BOOLEAN) {
			booleanResult = booleanResult & response->getBooleanResponse();
			continue;
		}

		if (response->getState() == ResponseState::VECTOR) {
			int insertToColumnIdex = findIndexOfColumnVariableName(response->getInsertToColumnName(), columnVariableNames);
			columnVariableNames.push_back(response->getVariableName());
			changeVectorResultsBasedOnResponses(response, oldState, newState, insertToColumnIdex);
		}
	}
}


void QueryEvaluator::changeVectorResultsBasedOnResponses(MethodEvaluatorResponse* response,
                                                         vector<vector<string>*>& oldState,
                                                         vector<vector<string>*>& newState,
                                                         int insertToColumnIdex) {
	/*First insert to eval results*/
	if (insertToColumnIdex < 0) {
		for (string singleResponse : response->getVectorResponse()) {
			vector<string>* newRow = new vector<string>();
			newRow->push_back(singleResponse);
			newState.push_back(newRow);
		}
		return;
	}


	for (string singleResponse : response->getVectorResponse()) {
		for (auto oldRow : oldState) {
			if (oldRow->at(insertToColumnIdex) == response->getInsertToColumnValue()) {
				vector<string>* newRow = new vector<string>(oldRow->begin(), oldRow->end());
				newRow->push_back(singleResponse);
				newState.push_back(newRow);
			}
		}
	}
}

MethodEvaluatorResponse* QueryEvaluator::parentEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep) {
	MethodEvaluatorResponse* response = new MethodEvaluatorResponse;
	/*Parent(x,7)*/
	if (leftParam->getState() == InvokationParamState::VARIABLE &&
		rightParam->getState() == InvokationParamState::VALUE) {
		auto vectorResult = pkbBrigde->getParentOf(rightParam->getValue(), goDeep);
		response->setState(ResponseState::VECTOR);
		response->setVectorResponse(vectorResult);
		response->setVariableName(leftParam->getVariableName());
		response->setVariableType(leftParam->getVariableType());
		response->setInsertToColumnName(rightParam->getVariableType());
		response->setInsertToColumnValue(rightParam->getValue());
	}
	/*Parent(7,x)*/
	else if (leftParam->getState() == InvokationParamState::VALUE &&
		rightParam->getState() == InvokationParamState::VARIABLE) {
		auto vectorResult = pkbBrigde->getChildrenOf(leftParam->getValue(), goDeep);
		response->setState(ResponseState::VECTOR);
		response->setVectorResponse(vectorResult);
		response->setVariableName(rightParam->getVariableName());
		response->setVariableType(rightParam->getVariableType());
		response->setInsertToColumnName(leftParam->getVariableName());
		response->setInsertToColumnValue(leftParam->getVariableName());
	}
	/*Parent(7,7)*/
	else if (leftParam->getState() == InvokationParamState::VALUE &&
		rightParam->getState() == InvokationParamState::VALUE) {
		auto booleanResult = pkbBrigde->isElemParentOf(leftParam->getValue(), rightParam->getValue(), goDeep);
		response->setState(ResponseState::BOOLEAN);
		response->setBooleanResponse(booleanResult);
	} else {
		throw QueryEvaluatorException("parentEvaluator - params are neither: (7, x) or (x, 7) or (7, 7), but instead are" + leftParam->toString() + " " + rightParam->toString());
	}

	return response;
}

InvokationParam* QueryEvaluator::changeParameterToInvokationParam(Parameter* parameter) {
	InvokationParam* invokationParam = new InvokationParam;

	/*Param is type ANY (_)*/
	if (parameter->getType() == ParameterType::ANY) {
		invokationParam->setState(InvokationParamState::ANY);
		invokationParam->setVariableName(parameter->getVariableName());
		invokationParam->setVariableType(parameter->getVariableType());
		return invokationParam;
	}

	if (parameter->getType() == ParameterType::VARIABLE) {
		invokationParam->setState(InvokationParamState::VARIABLE);
		invokationParam->setVariableName(parameter->getVariableName());
		invokationParam->setVariableType(parameter->getVariableType());
		return invokationParam;
	}

	if (parameter->getType() == ParameterType::INTEGER) {
		invokationParam->setState(InvokationParamState::VALUE);
		invokationParam->setValueType(ValueType::INTEGER);
		invokationParam->setValue(to_string(parameter->getIntegerValue()));
		invokationParam->setVariableName(parameter->getVariableName());
		invokationParam->setVariableType(parameter->getVariableType());
		return invokationParam;
	}

	if (parameter->getType() == ParameterType::STRING) {
		invokationParam->setState(InvokationParamState::VALUE);
		invokationParam->setValueType(ValueType::STRING);
		invokationParam->setValue(parameter->getStringValue());
		invokationParam->setVariableName(parameter->getVariableName());
		invokationParam->setVariableType(parameter->getVariableType());
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

		string variableType = findTypeOfDeclaredVariable(invokationParam->getVariableName());
		ValueType valueType;
		if (variableType == DeclarationKeywords::VARIABLE ||
			variableType == DeclarationKeywords::PROCEDURE) {
			valueType = ValueType::STRING;
		} else {
			valueType = ValueType::INTEGER;
		}

		vector<string> uniqueResults = findUniqueEvalResultsFromColumn(indexOfColumnVariable);
		for (string result : uniqueResults) {
			InvokationParam* newParam = invokationParam->copy();
			newParam->setState(InvokationParamState::VALUE);
			newParam->setValue(result);
			newParam->setValueType(valueType);

			params.push_back(newParam);
		}
		delete invokationParam;

		return params;
	}

	throw QueryEvaluatorException("generateParamsIncaseOfAvailableResults() shouldn't reach end of the function");
}


int QueryEvaluator::findIndexOfColumnVariableName(string varName) {
	return findIndexOfColumnVariableName(varName, columnVariableNames);
}


int QueryEvaluator::findIndexOfColumnVariableName(string varName, vector<string>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		if (arr.at(i) == varName) {
			return i;
		}
	}

	return -1;
}

string QueryEvaluator::findTypeOfDeclaredVariable(string varName) {
	for (auto declaredVariable : declaredVariables) {
		if (declaredVariable->getName() == varName) {
			return declaredVariable->getType();
		}
	}

	return "";
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

bool QueryEvaluator::getBooleanResult() const {
	return booleanResult;
}

void QueryEvaluator::setBooleanResult(const bool booleanResult) {
	this->booleanResult = booleanResult;
}
