#include "QueryEvaluator.h"

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

