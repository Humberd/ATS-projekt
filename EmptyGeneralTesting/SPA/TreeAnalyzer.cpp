#include "TreeAnalyzer.h"
#include "CallNode.h"

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

	container->statementTable = treeAnalyzer.analyzeStatementTable(rootNode);
	container->proceduresTable = treeAnalyzer.analyzeProceduresTable(rootNode);
	return container;
}

map<int, vector<int>> TreeAnalyzer::analyzeParentsTable(Node* rootNode) {
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


map<int, vector<int>> TreeAnalyzer::analyzeFollowsTable(Node* rootNode) {
	map<int, vector<int>> followsTable;

	for (auto procedure : rootNode->getChildren()) {
		followsTableStatementListWalker(followsTable, dynamic_cast<StatementListNode*>(procedure->getChild(0)));
	}

	return followsTable;
}

void TreeAnalyzer::followsTableStatementListWalker(map<int, vector<int>>& result, StatementListNode* statementListNode) const {
	

	if (statementListNode->getChildren().size() == 1) {
		followsTableCheckIfNodeIsValidParent(result, statementListNode->getChild(0));
		vector<int> lastValueVector = {};
		result.insert_or_assign(statementListNode->getChild(0)->getProgramLineNumber(), lastValueVector);
		return;
	}

	if (statementListNode->getChildren().size() > 1) {
		Node* previousNode = nullptr;

		for (auto child : statementListNode->getChildren()) {
			if (previousNode == nullptr) {
				previousNode = child;
				followsTableCheckIfNodeIsValidParent(result, child);
				continue;
			}

			vector<int> valueVector = { child->getProgramLineNumber() };

			result.insert_or_assign(previousNode->getProgramLineNumber(), valueVector);
			previousNode = child;

			followsTableCheckIfNodeIsValidParent(result, child);
		}

		vector<int> lastValueVector = {};
		result.insert_or_assign(previousNode->getProgramLineNumber(), lastValueVector);
	}

	
}

void TreeAnalyzer::followsTableCheckIfNodeIsValidParent(map<int, vector<int>>& result, Node* node) const {
	WhileNode* potentialWhileNode = dynamic_cast<WhileNode*>(node);
	if (potentialWhileNode != nullptr) {
		followsTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialWhileNode->getChild(1)));
		return;
	}

	IfNode* potentialIfNode = dynamic_cast<IfNode*>(node);
	if (potentialIfNode != nullptr) {
		followsTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(1)));
		followsTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(2)));
		return;
	}
}


map<string, vector<string>> TreeAnalyzer::analyzeCallsTable(Node* rootNode) {
	map<string, vector<string>> callsTable;

	for (auto procedure : rootNode->getChildren()) {
		set<string> result;
		callsTableStatementListWalker(result, dynamic_cast<StatementListNode*>(procedure->getChild(0)));
		
		ProcedureNode* procedureNode = dynamic_cast<ProcedureNode*>(procedure);
		vector<string> vecResult(result.size());
		vecResult.assign(result.begin(), result.end());

		callsTable.insert_or_assign(procedureNode->getName(), vecResult);
	}

	return callsTable;
}

void TreeAnalyzer::callsTableStatementListWalker(set<string>& result, StatementListNode* statementListNode) {
	for (auto child : statementListNode->getChildren()) {
		CallNode* potentialCallNode = dynamic_cast<CallNode*>(child);
		if (potentialCallNode != nullptr) {
			result.insert(potentialCallNode->getProcedureName());
		} else {
			callsTableCheckIfNodeIsContainer(result, child);
		}
	}
}

void TreeAnalyzer::callsTableCheckIfNodeIsContainer(set<string>& result, Node* node) {
	WhileNode* potentialWhileNode = dynamic_cast<WhileNode*>(node);
	if (potentialWhileNode != nullptr) {
		callsTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialWhileNode->getChild(1)));
		return;
	}

	IfNode* potentialIfNode = dynamic_cast<IfNode*>(node);
	if (potentialIfNode != nullptr) {
		callsTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(1)));
		callsTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(2)));
		return;
	}
}

map<int, vector<Node*>> TreeAnalyzer::analyzeStatementTable(Node* rootNode) {
	map<int, vector<Node*>> statementTable;

	for (auto procedure : rootNode->getChildren()) {
		statementTableStatementListWalker(statementTable, dynamic_cast<StatementListNode*>(procedure->getChild(0)));
	}

	return statementTable;
}

void TreeAnalyzer::statementTableStatementListWalker(map<int, vector<Node*>>& result, StatementListNode* statementListNode) {
	for (auto child : statementListNode->getChildren()) {
		vector<Node*> results = { child };
		result.insert_or_assign(child->getProgramLineNumber(), results);
		statementTableCheckIfNodeIsContainer(result, child);
	}
}

void TreeAnalyzer::statementTableCheckIfNodeIsContainer(map<int, vector<Node*>>& result, Node* node) {
	WhileNode* potentialWhileNode = dynamic_cast<WhileNode*>(node);
	if (potentialWhileNode != nullptr) {
		statementTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialWhileNode->getChild(1)));
		return;
	}

	IfNode* potentialIfNode = dynamic_cast<IfNode*>(node);
	if (potentialIfNode != nullptr) {
		statementTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(1)));
		statementTableStatementListWalker(result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(2)));
		return;
	}
}


vector<Node*> TreeAnalyzer::analyzeProceduresTable(Node* rootNode) {
	vector<Node*> proceduresTable;

	for (auto procedure : rootNode->getChildren()) {
		proceduresTable.push_back(procedure);
	}

	return proceduresTable;
}
