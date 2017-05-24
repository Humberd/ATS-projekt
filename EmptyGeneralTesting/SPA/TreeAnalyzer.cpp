#include "TreeAnalyzer.h"

TreeAnalyzer::TreeAnalyzer() {
}

TreeAnalyzer::~TreeAnalyzer() {
}

SpaDataContainer* TreeAnalyzer::analyzeTree(Node* rootNode) {
	TreeAnalyzer treeAnalyzer;

	SpaDataContainer* container = new SpaDataContainer;
	container->rootNode = rootNode;
	container->parentsTable = treeAnalyzer.analyzeParentsTable(rootNode);

	return container;
}

map<int, vector<int>> TreeAnalyzer::analyzeParentsTable(Node* rootNode) const {
	map<int, vector<int>> parentsTable;

	for (auto procedure : rootNode->getChildren()) {
		parentsTableProcedureWalker(parentsTable, dynamic_cast<ProcedureNode*>(procedure));
	}

	return parentsTable;
}


void TreeAnalyzer::parentsTableProcedureWalker(map<int, vector<int>>& result, ProcedureNode* procedureNode) const {
	for (auto child : procedureNode->getChild(0)->getChildren()) {
		parentsTableCheckValidParent(result, child);
	}
}

void TreeAnalyzer::parentsTableCheckValidParent(map<int, vector<int>>& result, Node* node) const {
	WhileNode* potentialWhileNode = dynamic_cast<WhileNode*>(node);
	if (potentialWhileNode != nullptr) {
		parentsTableAddWhile(result, potentialWhileNode);
	} else {
		IfNode* potentialIfNode = dynamic_cast<IfNode*>(node);
		if (potentialIfNode != nullptr) {
			parentsTableAddIf(result, potentialIfNode);
		}
	}
}

void TreeAnalyzer::parentsTableAddWhile(map<int, vector<int>>& result, WhileNode* whileNode) const {
	vector<int> children;

	for (auto child : whileNode->getChild(1)->getChildren()) {
		children.push_back(child->getProgramLineNumber());
		parentsTableCheckValidParent(result, child);
	}

	result.insert_or_assign(whileNode->getProgramLineNumber(), children);
}

void TreeAnalyzer::parentsTableAddIf(map<int, vector<int>>& result, IfNode* ifNode) const {
	vector<int> children;

	for (auto child : ifNode->getChild(1)->getChildren()) {
		children.push_back(child->getProgramLineNumber());
		parentsTableCheckValidParent(result, child);

	}

	for (auto child : ifNode->getChild(2)->getChildren()) {
		children.push_back(child->getProgramLineNumber());
		parentsTableCheckValidParent(result, child);

	}
	result.insert_or_assign(ifNode->getProgramLineNumber(), children);
}
