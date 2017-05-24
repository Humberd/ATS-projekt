#include "QueryEvaluator.h"
#include "QueryEvaluatorException.h"

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
