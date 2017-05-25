#include "TreeAnalyzer.h"
#include "CallNode.h"
#include "AssignNode.h"
#include "VariableNode.h"

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
	MultiMapResult* modifiesTableResults = treeAnalyzer.analyzeModifiesTable(rootNode);
	container->modifiesStatementTable = modifiesTableResults->statementMap;
	container->modifiesProcedureTable = modifiesTableResults->procedureMap;

	container->callsTable = treeAnalyzer.analyzeCallsTable(rootNode);

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

			vector<int> valueVector = {child->getProgramLineNumber()};

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


MultiMapResult* TreeAnalyzer::analyzeModifiesTable(Node* rootNode) {
	map<int, vector<string>> modifiesStatementTable;
	map<string, vector<string>> modifiesProcedureTable;

	vector<vector<InjectRequest*>> injectRequestsCollection;

	for (auto procedure : rootNode->getChildren()) {
		ProcedureNode* procedureNode = dynamic_cast<ProcedureNode*>(procedure);
		set<string> result;
		vector<InjectRequest*> injectRequests;
		modifiesTableStatementListWalker(modifiesStatementTable, result, dynamic_cast<StatementListNode*>(procedure->getChild(0)), injectRequests);
		vector<string> vecResult(result.begin(), result.end());
		modifiesProcedureTable.insert_or_assign(procedureNode->getName(), vecResult);
		for (auto injectRequest : injectRequests) {
			injectRequest->injectToProcedure = procedureNode->getName();
		}
		injectRequestsCollection.push_back(injectRequests);
	}


	MultiMapResult* multiMapResult = new MultiMapResult;
	multiMapResult->procedureMap = modifiesProcedureTable;
	multiMapResult->statementMap = modifiesStatementTable;
	multiMapResult->injectRequestsCollection = injectRequestsCollection;

	return multiMapResult;
}

void TreeAnalyzer::modifiesTableStatementListWalker(map<int, vector<string>>& globalResult,
                                                    set<string>& parentResult,
                                                    StatementListNode* statementListNode,
                                                    vector<InjectRequest*>& parentInjectRequests) {
	for (auto statementNode : statementListNode->getChildren()) {
		modifiesTableNodeChecker(globalResult, parentResult, statementNode, parentInjectRequests);
	}
}

/*todo zamienic getSourceLineNumber na getProgramLineNumber*/
void TreeAnalyzer::modifiesTableNodeChecker(map<int, vector<string>>& globalResult,
                                            set<string>& parentResult,
                                            Node* node,
                                            vector<InjectRequest*>& parentInjectRequests) {
	AssignNode* potentialAssignNode = dynamic_cast<AssignNode*>(node);
	if (potentialAssignNode != nullptr) {
		VariableNode* variableNode = dynamic_cast<VariableNode*>(potentialAssignNode->getChild(0));
		vector<string> result = {variableNode->getName()};
		globalResult.insert_or_assign(potentialAssignNode->getSourceLineNumber(), result);
		parentResult.insert(result.begin(), result.end());
		return;
	}

	WhileNode* potentialWhileNode = dynamic_cast<WhileNode*>(node);
	if (potentialWhileNode != nullptr) {
		VariableNode* variableNode = dynamic_cast<VariableNode*>(potentialWhileNode->getChild(0));
		set<string> result = {variableNode->getName()};
		vector<InjectRequest*> locInjectRequests;
		modifiesTableStatementListWalker(globalResult, result, dynamic_cast<StatementListNode*>(potentialWhileNode->getChild(1)), locInjectRequests);
		vector<string> vecResult(result.begin(), result.end());
		globalResult.insert_or_assign(potentialWhileNode->getSourceLineNumber(), vecResult);
		parentResult.insert(result.begin(), result.end());
		for (auto injectRequest : locInjectRequests) {
			injectRequest->injectToStatements.push_back(potentialWhileNode->getSourceLineNumber());
			parentInjectRequests.push_back(injectRequest);
		}
		return;
	}

	IfNode* potentialIfNode = dynamic_cast<IfNode*>(node);
	if (potentialIfNode != nullptr) {
		VariableNode* variableNode = dynamic_cast<VariableNode*>(potentialIfNode->getChild(0));
		set<string> result = {variableNode->getName()};
		vector<InjectRequest*> locInjectRequests;
		modifiesTableStatementListWalker(globalResult, result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(1)), locInjectRequests);
		modifiesTableStatementListWalker(globalResult, result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(2)), locInjectRequests);
		vector<string> vecResult(result.begin(), result.end());
		globalResult.insert_or_assign(potentialIfNode->getSourceLineNumber(), vecResult);
		parentResult.insert(result.begin(), result.end());
		for (auto injectRequest : locInjectRequests) {
			injectRequest->injectToStatements.push_back(potentialIfNode->getSourceLineNumber());
			parentInjectRequests.push_back(injectRequest);
		}
		return;
	}

	CallNode* potentialCallNode = dynamic_cast<CallNode*>(node);
	if (potentialCallNode != nullptr) {
		InjectRequest* injectRequest = new InjectRequest;
		injectRequest->callProcedure = potentialCallNode->getProcedureName();
		parentInjectRequests.push_back(injectRequest);
		return;
	}
}

map<string, vector<string>> TreeAnalyzer::analyzeCallsTable(Node* rootNode) {
	map<string, vector<string>> callsTable;

	for (auto procedure : rootNode->getChildren()) {
		set<string> result;
		callsTableStatementListWalker(result, dynamic_cast<StatementListNode*>(procedure->getChild(0)));

		ProcedureNode* procedureNode = dynamic_cast<ProcedureNode*>(procedure);
		vector<string> vecResult(result.begin(), result.end());

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
		vector<Node*> results = {child};
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
