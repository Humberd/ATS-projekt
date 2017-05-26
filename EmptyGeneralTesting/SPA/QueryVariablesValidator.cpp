#include "QueryVariablesValidator.h"
#include <algorithm>
#include "QueryVariablesValidatorException.h"
#include "DeclarationKeywords.h"

QueryVariablesValidator::QueryVariablesValidator() {
}

QueryVariablesValidator::~QueryVariablesValidator() {
}

void QueryVariablesValidator::validate(vector<DeclaredVariable*> declaredVariables,
                                       QueryRequest* queryRequest) const {
	checkIfVariablesWereDeclared(declaredVariables, queryRequest);
	checkIfVariablesHaveValidProperties(declaredVariables, queryRequest);
	addTypesToVariablesAndParams(declaredVariables, queryRequest);
}


void QueryVariablesValidator::checkIfVariablesWereDeclared(vector<DeclaredVariable*> declaredVariables,
                                                           QueryRequest* queryRequest) const {
	auto returnRequest = queryRequest->getReturnRequest();

	if (returnRequest->getReturnType() == ReturnType::VARIABLES) {
		/*Checking every variable in a returnRequest to see if it was declared*/
		auto returnVariables = returnRequest->getVariables();
		for (auto variable : returnVariables) {
			if (!doesVariableExist(variable->getName(), declaredVariables)) {
				throw QueryVariablesValidatorException("Variable '" + variable->getName() + "' used in a returnRequest was not declared");
			}
		}
	}
	

	/*Checking every variable in methodRequests*/
	for (auto methodRequest : queryRequest->getMethodRequests()) {
		if (methodRequest->getLeftParam()->getType() == ParameterType::VARIABLE) {
			if (!doesVariableExist(methodRequest->getLeftParam()->getVariableName(), declaredVariables)) {
				throw QueryVariablesValidatorException("Variable '" + methodRequest->getLeftParam()->getVariableName() + "' used in a methodRequest was not declared");
			}
		}
		if (methodRequest->getRightParam()->getType() == ParameterType::VARIABLE) {
			if (!doesVariableExist(methodRequest->getRightParam()->getVariableName(), declaredVariables)) {
				throw QueryVariablesValidatorException("Variable '" + methodRequest->getRightParam()->getVariableName() + "' used in a methodRequest was not declared");
			}
		}
	}

	/*Checking every variable in withRequests*/
	for (auto withRequest : queryRequest->getWithRequests()) {
		if (!doesVariableExist(withRequest->getLeftSideVariable()->getName(), declaredVariables)) {
			throw QueryVariablesValidatorException("Variable '" + withRequest->getLeftSideVariable()->getName() + "' used in a withRequest was not declared");
		}

		if (withRequest->getType() == WithType::VARIABLE) {
			if (!doesVariableExist(withRequest->getRightSideVariable()->getName(), declaredVariables)) {
				throw QueryVariablesValidatorException("Variable '" + withRequest->getRightSideVariable()->getName() + "' used in a withRequest was not declared");
			}
		}
	}
}

bool QueryVariablesValidator::doesVariableExist(string varName,
                                                vector<DeclaredVariable*> declaredVariables) const {
	return any_of(declaredVariables.begin(), declaredVariables.end(),
	              [varName](DeclaredVariable* variable) {
		              return variable->getName() == varName;
	              });
}

void QueryVariablesValidator::checkIfVariablesHaveValidProperties(vector<DeclaredVariable*> declaredVariables, QueryRequest* queryRequest) const {
	auto returnRequest = queryRequest->getReturnRequest();

	if (returnRequest->getReturnType() == ReturnType::VARIABLES) {
		/*Checking every variable in a returnRequest to see if it was declared*/
		auto returnVariables = returnRequest->getVariables();
		for (auto variable : returnVariables) {
			if (!variable->getPropertyName().empty()) {
				string varType = getVariableType(variable->getName(), declaredVariables);
				if (!doesPropertyExistOnType(variable->getPropertyName(), varType)) {
					throw QueryVariablesValidatorException("PropertyName '" + variable->getPropertyName() + "' of a variable '" + variable->getName() + "' does not exist on parameterType: '" + varType + "'");
				}
			}
		}
	}

	/*Checking every variable in withRequests*/
	for (auto withRequest : queryRequest->getWithRequests()) {
		if (!withRequest->getLeftSideVariable()->getPropertyName().empty()) {
			string varType = getVariableType(withRequest->getLeftSideVariable()->getName(), declaredVariables);
			if (!doesPropertyExistOnType(withRequest->getLeftSideVariable()->getPropertyName(), varType)) {
				throw QueryVariablesValidatorException("PropertyName '" + withRequest->getLeftSideVariable()->getPropertyName() + "' of a variable '" + withRequest->getLeftSideVariable()->getName() + "' does not exist on parameterType: '" + varType + "'");
			}
		}
		if (withRequest->getType() == WithType::VARIABLE) {
			if (!withRequest->getRightSideVariable()->getPropertyName().empty()) {
				string varType = getVariableType(withRequest->getRightSideVariable()->getName(), declaredVariables);
				if (!doesPropertyExistOnType(withRequest->getRightSideVariable()->getPropertyName(), varType)) {
					throw QueryVariablesValidatorException("PropertyName '" + withRequest->getRightSideVariable()->getPropertyName() + "' of a variable '" + withRequest->getRightSideVariable()->getName() + "' does not exist on parameterType: '" + varType + "'");
				}
			}
		}
	}
}

bool QueryVariablesValidator::doesPropertyExistOnType(string propertyName, string type) const {
	if (type == DeclarationKeywords::PROCEDURE) {
		return propertyName == "procName";
	} else if (type == DeclarationKeywords::CALL) {
		return propertyName == "procName";
	} else if (type == DeclarationKeywords::VARIABLE) {
		return propertyName == "varName";
	} else if (type == DeclarationKeywords::CONSTANT) {
		return propertyName == "value";
	} else if (type == DeclarationKeywords::STATEMENT) {
		return propertyName == "stmt";
	} else {
		return false;
	}
}

string QueryVariablesValidator::getVariableType(string varName,
                                                vector<DeclaredVariable*> declaredVariables) const {
	DeclaredVariable* foundVariable = *find_if(declaredVariables.begin(), declaredVariables.end(),
	                                           [varName](DeclaredVariable* variable) {
		                                           return variable->getName() == varName;
	                                           });

	return foundVariable->getType();
}

void QueryVariablesValidator::addTypesToVariablesAndParams(vector<DeclaredVariable*> declaredVariables,
                                                           QueryRequest* queryRequest) const {
	auto returnRequest = queryRequest->getReturnRequest();

	if (returnRequest->getReturnType() == ReturnType::VARIABLES) {
		/*Checking every variable in a returnRequest*/
		auto returnVariables = returnRequest->getVariables();
		for (auto variable : returnVariables) {
			string varType = getVariableType(variable->getName(), declaredVariables);
			variable->setType(varType);
		}
	}

	/*Checking every variable in methodRequests*/
	for (auto methodRequest : queryRequest->getMethodRequests()) {
		if (methodRequest->getLeftParam()->getType() == ParameterType::VARIABLE) {
			string varType = getVariableType(methodRequest->getLeftParam()->getVariableName(), declaredVariables);
			methodRequest->getLeftParam()->setVariableType(varType);
		}
		if (methodRequest->getRightParam()->getType() == ParameterType::VARIABLE) {
			string varType = getVariableType(methodRequest->getRightParam()->getVariableName(), declaredVariables);
			methodRequest->getRightParam()->setVariableType(varType);
		}
	}

	/*Checking every variable in withRequests*/
	for (auto withRequest : queryRequest->getWithRequests()) {
		string leftVarType = getVariableType(withRequest->getLeftSideVariable()->getName(), declaredVariables);
		withRequest->getLeftSideVariable()->setType(leftVarType);

		if (withRequest->getType() == WithType::VARIABLE) {
			string rightVarType = getVariableType(withRequest->getRightSideVariable()->getName(), declaredVariables);
			withRequest->getRightSideVariable()->setType(rightVarType);
		}
	}
}
