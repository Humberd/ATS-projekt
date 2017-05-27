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
#include <set>

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


vector<string> StatementsFilter::getNodesWithType(string type, SpaDataContainer* spaDataContainer) {
	if (type == DeclarationKeywords::VARIABLE) {
		return getAllVariables(spaDataContainer);
	}
	if (type == DeclarationKeywords::CONSTANT) {
		return getAllConstants(spaDataContainer);
	}
	if (type == DeclarationKeywords::PROCEDURE) {
		return getAllProcedures(spaDataContainer);
	}

	vector<string> newStatements;
	for (auto statatement : spaDataContainer->statementTable) {
		string stmt = to_string(statatement.first);
		auto desredNode = statatement.second.at(0);
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
		} else if (type == DeclarationKeywords::WHILE &&
			dynamic_cast<WhileNode*>(desredNode) != nullptr) {
			newStatements.push_back(stmt);
		}
	}
	return newStatements;
}


vector<string> StatementsFilter::getAllVariables(SpaDataContainer* spaDataContainer) {
	set<string> newStatements;

	for (auto entrySet : spaDataContainer->modifiesProcedureTable) {
		newStatements.insert(entrySet.second.begin(), entrySet.second.end());
	}

	for (auto entrySet : spaDataContainer->usesProcedureTable) {
		newStatements.insert(entrySet.second.begin(), entrySet.second.end());
	}

	vector<string> vecNewStatements(newStatements.begin(), newStatements.end());

	return vecNewStatements;
}

vector<string> StatementsFilter::getAllConstants(SpaDataContainer* spaDataContainer) {
	set<string> newStatements;

	getAllConstantsTreeTraverser(spaDataContainer->rootNode, newStatements);


	vector<string> vecNewStatements(newStatements.begin(), newStatements.end());

	return vecNewStatements;
}


void StatementsFilter::getAllConstantsTreeTraverser(Node* node, set<string>& globalConstants) {
	ConstantNode* constantNode = dynamic_cast<ConstantNode*>(node);
	if (constantNode != nullptr) {
		globalConstants.insert(to_string(constantNode->getValue()));
	}

	for (auto child : node->getChildren()) {
		getAllConstantsTreeTraverser(child, globalConstants);
	}
}

vector<string> StatementsFilter::getAllProcedures(SpaDataContainer* spaDataContainer) {
	set<string> newStatements;

	for (auto entrySet : spaDataContainer->callsTable) {
		newStatements.insert(entrySet.first);
	}

	vector<string> vecNewStatements(newStatements.begin(), newStatements.end());

	return vecNewStatements;
}
