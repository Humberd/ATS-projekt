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
	container->followsTable = treeAnalyzer.analyzeFollowsTable(rootNode);

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


map<int, vector<int>> TreeAnalyzer::analyzeFollowsTable(Node* rootNode) const {
	map<int, vector<int>> followsTable;

	for (auto procedure : rootNode->getChildren()) {
		followsTableStatementListWalker(followsTable, dynamic_cast<StatementListNode*>(procedure->getChild(0)));
	}

	return followsTable;
}

void TreeAnalyzer::followsTableStatementListWalker(map<int, vector<int>>& result, StatementListNode* statementListNode) const {
	Node* previousNode = nullptr;

	for (auto child : statementListNode->getChildren()) {
		if (previousNode == nullptr) {
			previousNode = child;
			continue;
		}
		vector<int> valueVector = { child->getProgramLineNumber() };

		result.insert_or_assign(previousNode->getProgramLineNumber(), valueVector);
		previousNode = child;

		followsTableCheckValidParent(result, child);
	}
}

void TreeAnalyzer::followsTableCheckValidParent(map<int, vector<int>>& result, Node* node) const {
	WhileNode* potentialWhileNode = dynamic_cast<WhileNode*>(node);
	if (potentialWhileNode != nullptr) {
		followsTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialWhileNode->getChild(1)));
	} else {
		IfNode* potentialIfNode = dynamic_cast<IfNode*>(node);
		if (potentialIfNode != nullptr) {
			followsTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(1)));
			followsTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(2)));
		}
	}
}
