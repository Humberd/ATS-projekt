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

void ProgramLineEvaluator::evaluate(Node* node) {
	int initialProgramLineNumber = 0;

	this->evaluate(node, initialProgramLineNumber);
}

void ProgramLineEvaluator::evaluate(Node* node, int& programLineNumber) {
	if (dynamic_cast<ProgramNode*>(node)) {
		node->setProgramLineNumber(-1);
		for (auto child : node->getChildren()) {
			this->evaluate(child, programLineNumber);
		}
	} else if (dynamic_cast<ProcedureNode*>(node)) {
		node->setProgramLineNumber(-1);
		for (auto child : node->getChildren()) {
			this->evaluate(child, programLineNumber);
		}
	} else if (dynamic_cast<StatementListNode*>(node)) {
		node->setProgramLineNumber(-1);
		for (auto child : node->getChildren()) {
			this->evaluate(child, programLineNumber);
		}
	} else if (dynamic_cast<AssignNode*>(node)) {
		programLineNumber++;
		node->setProgramLineNumber(programLineNumber);
		for (auto child : node->getChildren()) {
			this->evaluate(child, programLineNumber);
		}
	} else if (dynamic_cast<CallNode*>(node)) {
		programLineNumber++;
		node->setProgramLineNumber(programLineNumber);
		for (auto child : node->getChildren()) {
			this->evaluate(child, programLineNumber);
		}
	} else if (dynamic_cast<WhileNode*>(node)) {
		programLineNumber++;
		node->setProgramLineNumber(programLineNumber);
		for (auto child : node->getChildren()) {
			this->evaluate(child, programLineNumber);
		}
	} else if (dynamic_cast<IfNode*>(node)) {
		programLineNumber++;
		node->setProgramLineNumber(programLineNumber);
		this->evaluate(node->getChild(0), programLineNumber);
		this->evaluate(node->getChild(1), programLineNumber);
		this->evaluate(node->getChild(2), programLineNumber);
	} else if (dynamic_cast<ExpressionNode*>(node)) {
		node->setProgramLineNumber(programLineNumber);
		for (auto child : node->getChildren()) {
			this->evaluate(child, programLineNumber);
		}
	}
}
