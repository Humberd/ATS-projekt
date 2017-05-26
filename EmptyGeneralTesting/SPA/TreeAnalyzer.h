#pragma once
#include "SpaDataContainer.h"
#include "WhileNode.h"
#include "IfNode.h"
#include "ProcedureNode.h"
#include "StatementListNode.h"
#include <set>
#include "MultiMapResult.h"
#include "InjectRequest.h"
#include "InjectRequestsContainer.h"

using namespace std;

class TreeAnalyzer {
public:
	explicit TreeAnalyzer();
	~TreeAnalyzer();

	static SpaDataContainer* analyzeTree(Node* rootNode);

	map<int, vector<int>> analyzeParentsTable(Node* rootNode);
	void parentsTableProcedureWalker(map<int, vector<int>>& result, ProcedureNode* procedureNode) const;
	void parentsTableCheckValidParent(map<int, vector<int>>& result, Node* node) const;
	void parentsTableAddWhile(map<int, vector<int>>& result, WhileNode* whileNode) const;
	void parentsTableAddIf(map<int, vector<int>>& result, IfNode* ifNode) const;

	map<int, vector<int>> analyzeFollowsTable(Node* rootNode);
	void followsTableStatementListWalker(map<int, vector<int>>& result, StatementListNode* statementListNode) const;
	void followsTableCheckIfNodeIsValidParent(map<int, vector<int>>& result, Node* node) const;

	MultiMapResult* analyzeModifiesTable(Node* rootNode);
	void modifiesTableStatementListWalker(map<int, vector<string>>& globalResult,
	                                      set<string>& parentResult,
	                                      StatementListNode* statementListNode,
	                                      InjectRequestsContainer* injectRequestsContainer);
	void modifiesTableNodeChecker(map<int, vector<string>>& globalResult,
	                              set<string>& parentResult,
	                              Node* node,
	                              InjectRequestsContainer* injectRequestsContainer);
	void injectMissingCalls(map<int, vector<string>>& statementTable,
	                        map<string, vector<string>>& procedureTable,
	                        vector<InjectRequestsContainer*>& injectRequestsCollection);
	vector<InjectRequestsContainer*>::iterator findFulfilledRequest(vector<InjectRequestsContainer*>& injectRequestsCollection);

	map<string, vector<string>> analyzeCallsTable(Node* rootNode);
	void callsTableStatementListWalker(set<string>& result, StatementListNode* statementListNode);
	void callsTableCheckIfNodeIsContainer(set<string>& result, Node* node);

	map<int, vector<Node*>> analyzeStatementTable(Node* rootNode);
	void statementTableStatementListWalker(map<int, vector<Node*>>& result, StatementListNode* statementListNode);
	void statementTableCheckIfNodeIsContainer(map<int, vector<Node*>>& result, Node* node);

	vector<Node*> analyzeProceduresTable(Node* rootNode);
};
