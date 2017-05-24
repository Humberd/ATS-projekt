#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator(vector<DeclaredVariable*> declaredVariables,
                               QueryRequest* queryRequest): declaredVariables(declaredVariables), queryRequest(queryRequest) {
	pkbBrigde = new PkbBrigde;
}

QueryEvaluator::~QueryEvaluator() {
	for (vector<EvalUnit*>* result : evalResults) {
		for (auto unit : *result) {
			delete unit;
		}
		delete result;
	}
	evalResults.clear();
	columnVariableNames.clear();
}

void QueryEvaluator::evaluate() {
	queryRequest->getMethodRequests();
}

void QueryEvaluator::evaluateMethod(MethodRequest* methodRequest) {
}

void QueryEvaluator::evaluateParent(MethodRequest* parentRequest) {
	vector<int> result;
	string varName;

	if (parentRequest->getLeftParam()->getType() == ParameterType::INTEGER &&
		parentRequest->getRightParam()->getType() == ParameterType::VARIABLE) {
		result = pkbBrigde->getChildrenOf(parentRequest->getLeftParam()->getIntegerValue(), parentRequest->getGoDeep());
		varName = parentRequest->getRightParam()->getVariableName();
	} else if (parentRequest->getLeftParam()->getType() == ParameterType::VARIABLE &&
		parentRequest->getRightParam()->getType() == ParameterType::INTEGER) {
		result = pkbBrigde->getParentOf(parentRequest->getRightParam()->getIntegerValue(), parentRequest->getGoDeep());
		varName = parentRequest->getLeftParam()->getVariableName();
	}

}
