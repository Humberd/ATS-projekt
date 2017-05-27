#include "StatementsFilter.h"
#include <string>
#include "DeclarationKeywords.h"
#include "StatementNode.h"
#include "AssignNode.h"
#include "CallNode.h"
#include "IfNode.h"
#include "ConstantNode.h"
#include "ProcedureNode.h"
#include "VariableNode.h"
#include "WhileNode.h"
#include "QueryEvaluatorException.h"

StatementsFilter::StatementsFilter() {
}

StatementsFilter::~StatementsFilter() {
}

vector<string> StatementsFilter::filter(vector<string>& statements, string type, SpaDataContainer* spaDataContainer) {
	vector<string> newStatements;
	for (auto stmt : statements) {
		auto nodes = spaDataContainer->statementTable.at(stoi(stmt));
		auto desredNode = nodes.at(0);
		if (type == DeclarationKeywords::STATEMENT &&
			dynamic_cast<StatementNode*>(desredNode) != nullptr) {
			newStatements.push_back(stmt);
		} else if (type == DeclarationKeywords::ASSIGN &&
			dynamic_cast<AssignNode*>(desredNode) != nullptr) {
			newStatements.push_back(stmt);
		} else if (type == DeclarationKeywords::CALL &&
			dynamic_cast<CallNode*>(desredNode) != nullptr) {
			newStatements.push_back(stmt);
		} else if (type == DeclarationKeywords::IF &&
			dynamic_cast<IfNode*>(desredNode) != nullptr) {
			newStatements.push_back(stmt);
		} else if (type == DeclarationKeywords::CONSTANT &&
			dynamic_cast<ConstantNode*>(desredNode) != nullptr) {
			newStatements.push_back(stmt);
		} else if (type == DeclarationKeywords::PROCEDURE &&
			dynamic_cast<ProcedureNode*>(desredNode) != nullptr) {
			newStatements.push_back(stmt);
		} else if (type == DeclarationKeywords::VARIABLE &&
			dynamic_cast<VariableNode*>(desredNode) != nullptr) {
			newStatements.push_back(stmt);
		} else if (type == DeclarationKeywords::WHILE &&
			dynamic_cast<WhileNode*>(desredNode) != nullptr) {
			newStatements.push_back(stmt);
		} else {
			throw QueryEvaluatorException("StatementsFilter::filter() - unknown type: " + stmt);
		}
	}
	return newStatements;
}
