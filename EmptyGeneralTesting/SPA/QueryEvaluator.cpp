#include "QueryEvaluator.h"
#include "QueryEvaluatorException.h"
#include <algorithm>
#include "DeclarationKeywords.h"
#include "QueryMethods.h"

QueryEvaluator::QueryEvaluator() {
	pkbBrigde = nullptr;
	spaDataContainer = nullptr;
}

QueryEvaluator::QueryEvaluator(vector<DeclaredVariable*> declaredVariables,
                               QueryRequest* queryRequest,
                               SpaDataContainer* spaDataContainer): declaredVariables(declaredVariables), queryRequest(queryRequest), spaDataContainer(spaDataContainer) {
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

		if (initialLeftParam->getState() == InvokationParamState::ANY &&
			initialRightParam->getState() == InvokationParamState::ANY) {
			booleanResponses.push_back(true);
			continue;
		}

		auto leftParams = generateParamsIncaseOfAvailableResults(initialLeftParam, methodRequest->getMethodName(), 0);
		auto rightParams = generateParamsIncaseOfAvailableResults(initialRightParam, methodRequest->getMethodName(), 1);

		vector<MethodEvaluatorResponse*> responses;

		for (auto leftParam : leftParams) {
			for (auto rightParam: rightParams) {
				MethodEvaluatorResponse* response = evaluateMethod(methodRequest->getMethodName(), leftParam, rightParam, methodRequest->getGoDeep());
				if (response->getState() == ResponseState::VECTOR && spaDataContainer != nullptr) {
					response->setVectorResponse(StatementsFilter::filter(response->getVectorResponse(),
					                                                     findTypeOfDeclaredVariable(response->getVariableName()), spaDataContainer));
				}
				responses.push_back(response);
			}
		}

		vector<vector<string>*> newEvalResults;
		bool newBooleanResponse = true;
		changeResultsStateBasedOnResponses(responses, evalResults, newEvalResults, newBooleanResponse, columnVariableNames);

		for (auto res : evalResults) {
			delete res;
		}
		evalResults.clear();
		evalResults = newEvalResults;
		booleanResponses.push_back(newBooleanResponse);


		for (auto response : responses) {
			delete response;
		}
		responses.clear();
	}
}


vector<vector<string>> QueryEvaluator::evaluateReturn() {
	vector<vector<string>> response;

	ReturnRequest* returnRequest = this->queryRequest->getReturnRequest();

	if (returnRequest->getReturnType() == ReturnType::BOOLEAN) {
		response.resize(1);
		if (all_of(booleanResponses.begin(), booleanResponses.end(), [](bool boolResp) {
			           return boolResp == true;
		           })) {
			response[0].push_back("true");
		} else {
			response[0].push_back("false");
		}
		return response;
	}

	if (returnRequest->getReturnType() == ReturnType::VARIABLES) {

		vector<int> returnColumnIndexes;

		for (auto queryVariable : returnRequest->getVariables()) {
			if (findIndexOfColumnVariableName(queryVariable->getName()) < 0) {
				string varType = findTypeOfDeclaredVariable(queryVariable->getName());
				auto nodes = StatementsFilter::getNodesWithType(varType, spaDataContainer);

				if (queryVariable->getPropertyName() != "") {
					nodes = StatementsFilter::getPropertyValues(varType, queryVariable->getPropertyName(), spaDataContainer, nodes);
				}

				response.resize(nodes.size());
				for (unsigned int nodeIndex = 0; nodeIndex < nodes.size(); nodeIndex++) {
					response[nodeIndex].push_back(nodes.at(nodeIndex));
				}
				return response;
			} else {
				returnColumnIndexes.push_back(findIndexOfColumnVariableName(queryVariable->getName()));
			}
		}

		for (auto row : evalResults) {
			vector<string> outputRow;
			for (auto index : returnColumnIndexes) {
				outputRow.push_back(row->at(index));
			}

			response.push_back(outputRow);
		}
	}


	StatementsFilter::getNodesWithType("stmt", spaDataContainer);
	return response;
}

MethodEvaluatorResponse* QueryEvaluator::evaluateMethod(string methodName, InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep) {
	MethodEvaluatorResponse* response = nullptr;
	if (methodName == QueryMethods::PARENT) {
		response = parentEvaluator(leftParam, rightParam, goDeep);
	} else if (methodName == QueryMethods::FOLLOWS) {
		response = followsEvaluator(leftParam, rightParam, goDeep);
	} else if (methodName == QueryMethods::MODIFIES) {
		response = modifiesEvaluator(leftParam, rightParam, goDeep);
	} else if (methodName == QueryMethods::USES) {
		response = modifiesEvaluator(leftParam, rightParam, goDeep);
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
	if (responses.size() == 0) {
		throw QueryEvaluatorException("changeResultsStateBasedOnResponses() - responses should containt at least 1 item, but instead are empty!");
	}

	bool localResult = false;
	columnVariableNames.push_back(responses.at(0)->getVariableName());
	for (auto response : responses) {
		if (response->getState() == ResponseState::BOOLEAN) {
			localResult |= response->getBooleanResponse();
			continue;
		}

		if (response->getState() == ResponseState::VECTOR) {
			int insertToColumnIdex = findIndexOfColumnVariableName(response->getInsertToColumnName(), columnVariableNames);
			changeVectorResultsBasedOnResponses(response, oldState, newState, insertToColumnIdex);
		}
	}
	if (responses.at(0)->getState() == ResponseState::BOOLEAN) {
		booleanResult &= localResult;
	}
}


void QueryEvaluator::changeVectorResultsBasedOnResponses(MethodEvaluatorResponse* response,
                                                         vector<vector<string>*>& oldState,
                                                         vector<vector<string>*>& newState,
                                                         int insertToColumnIdex) {
	/*First insert to eval results*/
	if (insertToColumnIdex < 0) {
		if (oldState.size() != 0) {
			throw QueryEvaluatorException("changeVectorResultsBasedOnResponses() - insertToColumnIdex is less than 0. This means it should be the first column to inject, but unfortunately oldState is not empty. OldState size: " + to_string(oldState.size()));
		}
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
		response->setInsertToColumnValue(leftParam->getValue());
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


MethodEvaluatorResponse* QueryEvaluator::followsEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep) {
	MethodEvaluatorResponse* response = new MethodEvaluatorResponse;
	/*Parent(x,7)*/
	if (leftParam->getState() == InvokationParamState::VARIABLE &&
		rightParam->getState() == InvokationParamState::VALUE) {
		auto vectorResult = pkbBrigde->getFollowedBy(rightParam->getValue(), goDeep);
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
		auto vectorResult = pkbBrigde->getPrevious(leftParam->getValue(), goDeep);
		response->setState(ResponseState::VECTOR);
		response->setVectorResponse(vectorResult);
		response->setVariableName(rightParam->getVariableName());
		response->setVariableType(rightParam->getVariableType());
		response->setInsertToColumnName(leftParam->getVariableName());
		response->setInsertToColumnValue(leftParam->getValue());
	}
	/*Parent(7,7)*/
	else if (leftParam->getState() == InvokationParamState::VALUE &&
		rightParam->getState() == InvokationParamState::VALUE) {
		auto booleanResult = pkbBrigde->isElemFollowing(leftParam->getValue(), rightParam->getValue(), goDeep);
		response->setState(ResponseState::BOOLEAN);
		response->setBooleanResponse(booleanResult);
	} else {
		throw QueryEvaluatorException("followsEvaluator - params are neither: (7, x) or (x, 7) or (7, 7), but instead are" + leftParam->toString() + " " + rightParam->toString());
	}

	return response;
}

MethodEvaluatorResponse* QueryEvaluator::modifiesEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep) {
	MethodEvaluatorResponse* response = new MethodEvaluatorResponse;
	/*Modifies(7,x) || Modifies("Earth",x)*/
	if (leftParam->getState() == InvokationParamState::VALUE &&
		rightParam->getState() == InvokationParamState::VARIABLE) {
		vector<string> vectorResult;
		/*Modifies(7,x)*/
		if (leftParam->getValueType() == ValueType::INTEGER) {
			vectorResult = pkbBrigde->getVariableThatIsModifiedByStatement(leftParam->getValue());
		}
		/*Modifies("Earth",x)*/
		else {
			vectorResult = pkbBrigde->getVariableThatIsModifiedByProcedure(leftParam->getValue());
		}
		response->setState(ResponseState::VECTOR);
		response->setVectorResponse(vectorResult);
		response->setVariableName(rightParam->getVariableName());
		response->setVariableType(rightParam->getVariableType());
		response->setInsertToColumnName(leftParam->getVariableName());
		response->setInsertToColumnValue(leftParam->getValue());
	}
	/*Modifies(stat,"a") || Modifies(proc,"a")*/
	else if (leftParam->getState() == InvokationParamState::VARIABLE &&
		rightParam->getState() == InvokationParamState::VALUE) {
		vector<string> vectorResult;

		string varType = findTypeOfDeclaredVariable(leftParam->getVariableName());
		/*Modifies(proc,"a")*/
		if (varType == DeclarationKeywords::PROCEDURE) {
			vectorResult = pkbBrigde->getProceduresThatModifies(rightParam->getValue());
		}
		/*Modifies(stat,"a")*/
		else {
			vectorResult = pkbBrigde->getStatementsThatModifies(rightParam->getValue());
		}

		response->setState(ResponseState::VECTOR);
		response->setVectorResponse(vectorResult);
		response->setVariableName(leftParam->getVariableName());
		response->setVariableType(leftParam->getVariableType());
		response->setInsertToColumnName(rightParam->getVariableName());
		response->setInsertToColumnValue(rightParam->getValue());
	}

	/*Modifies("procName","x") || Modifies(4, "x")*/
	else if (leftParam->getState() == InvokationParamState::VALUE &&
		rightParam->getState() == InvokationParamState::VALUE) {
		bool booleanResult;
		/*Modifies("procName","x")*/
		if (leftParam->getValueType() == ValueType::STRING) {
			booleanResult = pkbBrigde->isProceduretModifyingVariable(leftParam->getValue(), rightParam->getValue());
		}
		/*Modifies(4, "x")*/
		else {
			booleanResult = pkbBrigde->isStatementModifyingVariable(leftParam->getValue(), rightParam->getValue());
		}
		response->setState(ResponseState::BOOLEAN);
		response->setBooleanResponse(booleanResult);
	} else {
		throw QueryEvaluatorException("modifiesEvaluator - params are neither: (7, x) or (x, 7) or (7, 7), but instead are" + leftParam->toString() + " " + rightParam->toString());
	}

	return response;
}


MethodEvaluatorResponse* QueryEvaluator::usesEvaluator(InvokationParam* leftParam, InvokationParam* rightParam, bool goDeep) {
	MethodEvaluatorResponse* response = new MethodEvaluatorResponse;
	/*Uses(7,x) || Uses("Earth",x)*/
	if (leftParam->getState() == InvokationParamState::VALUE &&
		rightParam->getState() == InvokationParamState::VARIABLE) {
		vector<string> vectorResult;
		/*Uses(7,x)*/
		if (leftParam->getValueType() == ValueType::INTEGER) {
			vectorResult = pkbBrigde->getVariablesUsedByStatement(leftParam->getValue());
		}
		/*Uses("Earth",x)*/
		else {
			vectorResult = pkbBrigde->getVariablesUsedByProcedure(leftParam->getValue());
		}
		response->setState(ResponseState::VECTOR);
		response->setVectorResponse(vectorResult);
		response->setVariableName(rightParam->getVariableName());
		response->setVariableType(rightParam->getVariableType());
		response->setInsertToColumnName(leftParam->getVariableName());
		response->setInsertToColumnValue(leftParam->getValue());
	}
	/*Uses(stat,"a") || Uses(proc,"a")*/
	else if (leftParam->getState() == InvokationParamState::VARIABLE &&
		rightParam->getState() == InvokationParamState::VALUE) {
		vector<string> vectorResult;

		string varType = findTypeOfDeclaredVariable(leftParam->getVariableName());
		/*Uses(proc,"a")*/
		if (varType == DeclarationKeywords::PROCEDURE) {
			vectorResult = pkbBrigde->getProceduresThatUses(rightParam->getValue());
		}
		/*Uses(stat,"a")*/
		else {
			vectorResult = pkbBrigde->getStatementsThatUses(rightParam->getValue());
		}

		response->setState(ResponseState::VECTOR);
		response->setVectorResponse(vectorResult);
		response->setVariableName(leftParam->getVariableName());
		response->setVariableType(leftParam->getVariableType());
		response->setInsertToColumnName(rightParam->getVariableName());
		response->setInsertToColumnValue(rightParam->getValue());
	}

	/*Uses("procName","x") || Uses(4, "x")*/
	else if (leftParam->getState() == InvokationParamState::VALUE &&
		rightParam->getState() == InvokationParamState::VALUE) {
		bool booleanResult;
		/*Uses("procName","x")*/
		if (leftParam->getValueType() == ValueType::STRING) {
			booleanResult = pkbBrigde->isProcedureUsingVariable(leftParam->getValue(), rightParam->getValue());
		}
		/*Uses(4, "x")*/
		else {
			booleanResult = pkbBrigde->isStatementUsingVariable(leftParam->getValue(), rightParam->getValue());
		}
		response->setState(ResponseState::BOOLEAN);
		response->setBooleanResponse(booleanResult);
	} else {
		throw QueryEvaluatorException("usesEvaluator - params are neither: (7, x) or (x, 7) or (7, 7), but instead are" + leftParam->toString() + " " + rightParam->toString());
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

vector<InvokationParam*> QueryEvaluator::generateParamsIncaseOfAvailableResults(InvokationParam* invokationParam, string method, int paramNumber) {
	vector<InvokationParam*> params;

	if (invokationParam->getState() == InvokationParamState::VALUE) {
		params.push_back(invokationParam);
		return params;
	}

	if (invokationParam->getState() == InvokationParamState::ANY) {
		if (method == QueryMethods::MODIFIES || method == QueryMethods::USES) {
			if (paramNumber == 1) {
				for (auto variable : StatementsFilter::getAllVariables(spaDataContainer)) {
					InvokationParam* param = invokationParam->copy();
					param->setState(InvokationParamState::VALUE);
					param->setValueType(ValueType::STRING);
					param->setValue(variable);
					params.push_back(param);
				}
				delete invokationParam;

				return params;
			} else if (paramNumber == 0) {
				for (auto entrySet : spaDataContainer->statementTable) {
					InvokationParam* param = invokationParam->copy();
					param->setState(InvokationParamState::VALUE);
					param->setValueType(ValueType::INTEGER);
					param->setValue(to_string(entrySet.first));
					params.push_back(param);
				}
				for (auto procedure : StatementsFilter::getAllProcedures(spaDataContainer)) {
					InvokationParam* param = invokationParam->copy();
					param->setState(InvokationParamState::VALUE);
					param->setValueType(ValueType::STRING);
					param->setValue(procedure);
					params.push_back(param);
				}

				delete invokationParam;

				return params;
			}

		} else {
			for (auto entrySet : spaDataContainer->statementTable) {
				InvokationParam* param = invokationParam->copy();
				param->setState(InvokationParamState::VALUE);
				param->setValueType(ValueType::INTEGER);
				param->setValue(to_string(entrySet.first));
				params.push_back(param);
			}
			delete invokationParam;

			return params;
		}
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


SpaDataContainer* QueryEvaluator::getSpaDataContainer() const {
	return spaDataContainer;
}

void QueryEvaluator::setSpaDataContainer(SpaDataContainer* const spaDataContainer) {
	this->spaDataContainer = spaDataContainer;
}

vector<bool> QueryEvaluator::getBooleanResponses() const {
	return booleanResponses;
}

void QueryEvaluator::setBooleanResponses(const vector<bool> booleanResponses) {
	this->booleanResponses = booleanResponses;
}
