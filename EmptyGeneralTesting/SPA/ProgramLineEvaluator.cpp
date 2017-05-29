#include "ProgramLineEvaluator.h"
#include "ProgramNode.h"
#include "ProcedureNode.h"
#include "StatementListNode.h"
#include "AssignNode.h"
#include "CallNode.h"
#include "WhileNode.h"
#include "IfNode.h"
#include "ExpressionNode.h"

ProgramLineEvaluator::ProgramLineEvaluator() {
}

ProgramLineEvaluator::~ProgramLineEvaluator() {
}

void ProgramLineEvaluator::evaluate(Node* node) const {
	int initialProgramLineNumber = 0;

	this->evaluate(node, initialProgramLineNumber);
}

void ProgramLineEvaluator::evaluate(Node* node, int& programLineNumber) const {
	if (dynamic_cast<ProgramNode*>(node)) {
		node->setProgramLineNumber(-1);
	} else if (dynamic_cast<ProcedureNode*>(node)) {
		node->setProgramLineNumber(-1);
	} else if (dynamic_cast<StatementListNode*>(node)) {
		node->setProgramLineNumber(-1);
	} else if (dynamic_cast<StatementNode*>(node)) {
		programLineNumber++;
		node->setProgramLineNumber(programLineNumber);
	} else if (dynamic_cast<ExpressionNode*>(node)) {
		node->setProgramLineNumber(programLineNumber);
	}

	for (auto child : node->getChildren()) {
		this->evaluate(child, programLineNumber);
	}
}
