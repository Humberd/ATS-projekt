#include "TreeAnalyzer.h"
#include "CallNode.h"
#include "AssignNode.h"
#include "VariableNode.h"
#include <algorithm>
#include "TreeAnalyzerException.h"
#include "ConstantNode.h"

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
	MultiMapResult* usesTableResults = treeAnalyzer.analyzeUsesTable(rootNode);
	container->usesStatementTable = usesTableResults->statementMap;
	container->usesProcedureTable = usesTableResults->procedureMap;
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


MultiMapResult* TreeAnalyzer::analyzeUsesTable(Node* rootNode) {
	map<int, vector<string>> usesStatementTable;
	map<string, vector<string>> usesProcedureTable;

	vector<InjectRequestsContainer*> injectRequestsCollection;

	for (auto procedure : rootNode->getChildren()) {
		ProcedureNode* procedureNode = dynamic_cast<ProcedureNode*>(procedure);
		set<string> result;
		InjectRequestsContainer* localInjectContainer = new InjectRequestsContainer;
		usesTableStatementListWalker(usesStatementTable, result, dynamic_cast<StatementListNode*>(procedure->getChild(0)), localInjectContainer);
		vector<string> vecResult(result.begin(), result.end());
		usesProcedureTable.insert_or_assign(procedureNode->getName(), vecResult);
		localInjectContainer->procedureName = procedureNode->getName();
		injectRequestsCollection.push_back(localInjectContainer);
	}

	usesTableInjectMissingCalls(usesStatementTable, usesProcedureTable, injectRequestsCollection);

	MultiMapResult* multiMapResult = new MultiMapResult;
	multiMapResult->procedureMap = usesProcedureTable;
	multiMapResult->statementMap = usesStatementTable;

	return multiMapResult;
}

void TreeAnalyzer::usesTableStatementListWalker(map<int, vector<string>>& globalResult, set<string>& parentResult, StatementListNode* statementListNode, InjectRequestsContainer* parentRequestsContainer) {
	for (auto statementNode : statementListNode->getChildren()) {
		usesTableNodeChecker(globalResult, parentResult, statementNode, parentRequestsContainer);
	}
}

void TreeAnalyzer::usesTableGetVariablesFromNode(set<string>& results, ExpressionNode* expressionNode) {
	VariableNode* potentialVariableNode = dynamic_cast<VariableNode*>(expressionNode);
	if (potentialVariableNode != nullptr) {
		results.insert(potentialVariableNode->getName());
		return;
	}

	ConstantNode* potentialConstantNode = dynamic_cast<ConstantNode*>(expressionNode);
	if (potentialConstantNode != nullptr) {
		//do nothing
		return;
	}

	usesTableGetVariablesFromNode(results, dynamic_cast<ExpressionNode*>(expressionNode->getChild(0)));
	usesTableGetVariablesFromNode(results, dynamic_cast<ExpressionNode*>(expressionNode->getChild(1)));
}

/*todo redo VariableNode*/
void TreeAnalyzer::usesTableNodeChecker(map<int, vector<string>>& globalResult, set<string>& parentResult, Node* node, InjectRequestsContainer* parentRequestsContainer) {
	AssignNode* potentialAssignNode = dynamic_cast<AssignNode*>(node);
	if (potentialAssignNode != nullptr) {
		set<string> result;
		usesTableGetVariablesFromNode(result, dynamic_cast<ExpressionNode*>(potentialAssignNode->getChild(1)));
		vector<string> vecResult(result.begin(), result.end());
		globalResult.insert_or_assign(potentialAssignNode->getProgramLineNumber(), vecResult);
		parentResult.insert(vecResult.begin(), vecResult.end());
		return;
	}

	WhileNode* potentialWhileNode = dynamic_cast<WhileNode*>(node);
	if (potentialWhileNode != nullptr) {
		VariableNode* variableNode = dynamic_cast<VariableNode*>(potentialWhileNode->getChild(0));
		set<string> result = { variableNode->getName() };
		InjectRequestsContainer* localInjectContainer = new InjectRequestsContainer;
		usesTableStatementListWalker(globalResult, result, dynamic_cast<StatementListNode*>(potentialWhileNode->getChild(1)), localInjectContainer);
		vector<string> vecResult(result.begin(), result.end());
		globalResult.insert_or_assign(potentialWhileNode->getProgramLineNumber(), vecResult);
		parentResult.insert(result.begin(), result.end());
		for (auto injectRequest : localInjectContainer->injectRequests) {
			injectRequest->injectToStatements.push_back(potentialWhileNode->getProgramLineNumber());
			parentRequestsContainer->injectRequests.push_back(injectRequest);
		}
		delete localInjectContainer;
		return;
	}

	IfNode* potentialIfNode = dynamic_cast<IfNode*>(node);
	if (potentialIfNode != nullptr) {
		VariableNode* variableNode = dynamic_cast<VariableNode*>(potentialIfNode->getChild(0));
		set<string> result = { variableNode->getName() };
		InjectRequestsContainer* localInjectContainer = new InjectRequestsContainer;
		usesTableStatementListWalker(globalResult, result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(1)), localInjectContainer);
		usesTableStatementListWalker(globalResult, result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(2)), localInjectContainer);
		vector<string> vecResult(result.begin(), result.end());
		globalResult.insert_or_assign(potentialIfNode->getProgramLineNumber(), vecResult);
		parentResult.insert(result.begin(), result.end());
		for (auto injectRequest : localInjectContainer->injectRequests) {
			injectRequest->injectToStatements.push_back(potentialIfNode->getProgramLineNumber());
			parentRequestsContainer->injectRequests.push_back(injectRequest);
		}
		delete localInjectContainer;
		return;
	}

	CallNode* potentialCallNode = dynamic_cast<CallNode*>(node);
	if (potentialCallNode != nullptr) {
		InjectRequest* injectRequest = new InjectRequest;
		injectRequest->callProcedure = potentialCallNode->getProcedureName();
		injectRequest->injectToStatements.push_back(potentialCallNode->getProgramLineNumber());
		parentRequestsContainer->injectRequests.push_back(injectRequest);

		vector<string> vecResult;
		globalResult.insert_or_assign(potentialCallNode->getProgramLineNumber(), vecResult);
		return;
	}
}

void TreeAnalyzer::usesTableInjectMissingCalls(map<int, vector<string>>& statementTable, map<string, vector<string>>& procedureTable, vector<InjectRequestsContainer*>& injectRequestsCollection) {
	if (injectRequestsCollection.size() == 0) {
		return;
	}
	auto fulfilledRequestIterator = usesTableFindFulfilledRequest(injectRequestsCollection);
	if (fulfilledRequestIterator == injectRequestsCollection.end()) {
		throw TreeAnalyzerException("usesTable -> injectMissingCalls -> injectRequestsCollection is greater then 0. Cannot find InjectRequestsContainer that has injectRequests with size 0");
	}

	InjectRequestsContainer* fulfilledRequest = *fulfilledRequestIterator;

	for (signed i = 0; i < injectRequestsCollection.size(); i++) {
		auto requestsContainer = injectRequestsCollection.at(i);

		if (requestsContainer->injectRequests.size() == 0) {
			continue;
		}

		for (signed int j = 0; j < requestsContainer->injectRequests.size(); j++) {
			auto injectRequest = requestsContainer->injectRequests.at(j);

			if (injectRequest->callProcedure == fulfilledRequest->procedureName) {

				/*Inject fullFilledRequestDeps to all the statements*/
				for (auto injectToStatement : injectRequest->injectToStatements) {
					set<string> previousStatementDependencies(statementTable.at(injectToStatement).begin(), statementTable.at(injectToStatement).end());
					previousStatementDependencies.insert(procedureTable.at(fulfilledRequest->procedureName).begin(), procedureTable.at(fulfilledRequest->procedureName).end());
					vector<string> newStatementDependencies(previousStatementDependencies.begin(), previousStatementDependencies.end());
					statementTable.insert_or_assign(injectToStatement, newStatementDependencies);
				}

				/*Inject fulfilledRequestDeps to a procedure*/
				set<string> previousProcedureDependencies(procedureTable.at(requestsContainer->procedureName).begin(), procedureTable.at(requestsContainer->procedureName).end());
				previousProcedureDependencies.insert(procedureTable.at(fulfilledRequest->procedureName).begin(), procedureTable.at(fulfilledRequest->procedureName).end());
				vector<string> newProcedureDependencies(previousProcedureDependencies.begin(), previousProcedureDependencies.end());
				procedureTable.insert_or_assign(requestsContainer->procedureName, newProcedureDependencies);

				requestsContainer->injectRequests.erase(requestsContainer->injectRequests.begin() + j);
				j--;
			}
		}
	}

	injectRequestsCollection.erase(remove_if(injectRequestsCollection.begin(), injectRequestsCollection.end(),
		[fulfilledRequest](InjectRequestsContainer* item) {
		return item->procedureName == fulfilledRequest->procedureName;
	}));


	usesTableInjectMissingCalls(statementTable, procedureTable, injectRequestsCollection);
}

vector<InjectRequestsContainer*>::iterator TreeAnalyzer::usesTableFindFulfilledRequest(vector<InjectRequestsContainer*>& injectRequestsCollection) {
	auto fulfilledRequest = find_if(injectRequestsCollection.begin(), injectRequestsCollection.end(),
		[](InjectRequestsContainer* item) {
		return item->injectRequests.size() == 0;
	});

	return fulfilledRequest;
}

MultiMapResult* TreeAnalyzer::analyzeModifiesTable(Node* rootNode) {
	map<int, vector<string>> modifiesStatementTable;
	map<string, vector<string>> modifiesProcedureTable;

	vector<InjectRequestsContainer*> injectRequestsCollection;

	for (auto procedure : rootNode->getChildren()) {
		ProcedureNode* procedureNode = dynamic_cast<ProcedureNode*>(procedure);
		set<string> result;
		InjectRequestsContainer* localInjectContainer = new InjectRequestsContainer;
		modifiesTableStatementListWalker(modifiesStatementTable, result, dynamic_cast<StatementListNode*>(procedure->getChild(0)), localInjectContainer);
		vector<string> vecResult(result.begin(), result.end());
		modifiesProcedureTable.insert_or_assign(procedureNode->getName(), vecResult);
		localInjectContainer->procedureName = procedureNode->getName();
		injectRequestsCollection.push_back(localInjectContainer);
	}

	modifiesTableInjectMissingCalls(modifiesStatementTable, modifiesProcedureTable, injectRequestsCollection);

	MultiMapResult* multiMapResult = new MultiMapResult;
	multiMapResult->procedureMap = modifiesProcedureTable;
	multiMapResult->statementMap = modifiesStatementTable;

	return multiMapResult;
}


void TreeAnalyzer::modifiesTableInjectMissingCalls(map<int, vector<string>>& statementTable,
                                      map<string, vector<string>>& procedureTable,
                                      vector<InjectRequestsContainer*>& injectRequestsCollection) {
	if (injectRequestsCollection.size() == 0) {
		return;
	}
	auto fulfilledRequestIterator = modifiesTableFindFulfilledRequest(injectRequestsCollection);
	if (fulfilledRequestIterator == injectRequestsCollection.end()) {
		throw TreeAnalyzerException("modifiesTable -> injectMissingCalls -> injectRequestsCollection is greater then 0. Cannot find InjectRequestsContainer that has injectRequests with size 0");
	}

	InjectRequestsContainer* fulfilledRequest = *fulfilledRequestIterator;

	for (signed i = 0; i < injectRequestsCollection.size(); i++) {
		auto requestsContainer = injectRequestsCollection.at(i);

		if (requestsContainer->injectRequests.size() == 0) {
			continue;
		}

		for (signed int j = 0; j < requestsContainer->injectRequests.size(); j++) {
			auto injectRequest = requestsContainer->injectRequests.at(j);

			if (injectRequest->callProcedure == fulfilledRequest->procedureName) {

				/*Inject fullFilledRequestDeps to all the statements*/
				for (auto injectToStatement : injectRequest->injectToStatements) {
					set<string> previousStatementDependencies(statementTable.at(injectToStatement).begin(), statementTable.at(injectToStatement).end());
					previousStatementDependencies.insert(procedureTable.at(fulfilledRequest->procedureName).begin(), procedureTable.at(fulfilledRequest->procedureName).end());
					vector<string> newStatementDependencies(previousStatementDependencies.begin(), previousStatementDependencies.end());
					statementTable.insert_or_assign(injectToStatement, newStatementDependencies);
				}

				/*Inject fulfilledRequestDeps to a procedure*/
				set<string> previousProcedureDependencies(procedureTable.at(requestsContainer->procedureName).begin(), procedureTable.at(requestsContainer->procedureName).end());
				previousProcedureDependencies.insert(procedureTable.at(fulfilledRequest->procedureName).begin(), procedureTable.at(fulfilledRequest->procedureName).end());
				vector<string> newProcedureDependencies(previousProcedureDependencies.begin(), previousProcedureDependencies.end());
				procedureTable.insert_or_assign(requestsContainer->procedureName, newProcedureDependencies);

				requestsContainer->injectRequests.erase(requestsContainer->injectRequests.begin() + j);
				j--;
			}
		}
	}

	injectRequestsCollection.erase(remove_if(injectRequestsCollection.begin(), injectRequestsCollection.end(),
	                                         [fulfilledRequest](InjectRequestsContainer* item) {
		                                         return item->procedureName == fulfilledRequest->procedureName;
	                                         }));


	modifiesTableInjectMissingCalls(statementTable, procedureTable, injectRequestsCollection);
}

vector<InjectRequestsContainer*>::iterator TreeAnalyzer::modifiesTableFindFulfilledRequest(vector<InjectRequestsContainer*>& injectRequestsCollection) {
	auto fulfilledRequest = find_if(injectRequestsCollection.begin(), injectRequestsCollection.end(),
	                                [](InjectRequestsContainer* item) {
		                                return item->injectRequests.size() == 0;
	                                });

	return fulfilledRequest;
}

void TreeAnalyzer::modifiesTableStatementListWalker(map<int, vector<string>>& globalResult,
                                                    set<string>& parentResult,
                                                    StatementListNode* statementListNode,
                                                    InjectRequestsContainer* parentRequestsContainer) {
	for (auto statementNode : statementListNode->getChildren()) {
		modifiesTableNodeChecker(globalResult, parentResult, statementNode, parentRequestsContainer);
	}
}

void TreeAnalyzer::modifiesTableNodeChecker(map<int, vector<string>>& globalResult,
                                            set<string>& parentResult,
                                            Node* node,
                                            InjectRequestsContainer* parentRequestsContainer) {
	AssignNode* potentialAssignNode = dynamic_cast<AssignNode*>(node);
	if (potentialAssignNode != nullptr) {
		VariableNode* variableNode = dynamic_cast<VariableNode*>(potentialAssignNode->getChild(0));
		vector<string> result = {variableNode->getName()};
		globalResult.insert_or_assign(potentialAssignNode->getProgramLineNumber(), result);
		parentResult.insert(result.begin(), result.end());
		return;
	}

	WhileNode* potentialWhileNode = dynamic_cast<WhileNode*>(node);
	if (potentialWhileNode != nullptr) {
		VariableNode* variableNode = dynamic_cast<VariableNode*>(potentialWhileNode->getChild(0));
		set<string> result = {variableNode->getName()};
		InjectRequestsContainer* localInjectContainer = new InjectRequestsContainer;
		modifiesTableStatementListWalker(globalResult, result, dynamic_cast<StatementListNode*>(potentialWhileNode->getChild(1)), localInjectContainer);
		vector<string> vecResult(result.begin(), result.end());
		globalResult.insert_or_assign(potentialWhileNode->getProgramLineNumber(), vecResult);
		parentResult.insert(result.begin(), result.end());
		for (auto injectRequest : localInjectContainer->injectRequests) {
			injectRequest->injectToStatements.push_back(potentialWhileNode->getProgramLineNumber());
			parentRequestsContainer->injectRequests.push_back(injectRequest);
		}
		delete localInjectContainer;
		return;
	}

	IfNode* potentialIfNode = dynamic_cast<IfNode*>(node);
	if (potentialIfNode != nullptr) {
		VariableNode* variableNode = dynamic_cast<VariableNode*>(potentialIfNode->getChild(0));
		set<string> result = {variableNode->getName()};
		InjectRequestsContainer* localInjectContainer = new InjectRequestsContainer;
		modifiesTableStatementListWalker(globalResult, result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(1)), localInjectContainer);
		modifiesTableStatementListWalker(globalResult, result, dynamic_cast<StatementListNode*>(potentialIfNode->getChild(2)), localInjectContainer);
		vector<string> vecResult(result.begin(), result.end());
		globalResult.insert_or_assign(potentialIfNode->getProgramLineNumber(), vecResult);
		parentResult.insert(result.begin(), result.end());
		for (auto injectRequest : localInjectContainer->injectRequests) {
			injectRequest->injectToStatements.push_back(potentialIfNode->getProgramLineNumber());
			parentRequestsContainer->injectRequests.push_back(injectRequest);
		}
		delete localInjectContainer;
		return;
	}

	CallNode* potentialCallNode = dynamic_cast<CallNode*>(node);
	if (potentialCallNode != nullptr) {
		InjectRequest* injectRequest = new InjectRequest;
		injectRequest->callProcedure = potentialCallNode->getProcedureName();
		injectRequest->injectToStatements.push_back(potentialCallNode->getProgramLineNumber());
		parentRequestsContainer->injectRequests.push_back(injectRequest);

		vector<string> vecResult;
		globalResult.insert_or_assign(potentialCallNode->getProgramLineNumber(), vecResult);
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
