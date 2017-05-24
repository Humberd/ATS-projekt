#pragma once
#include "SpaDataContainer.h"
#include "WhileNode.h"
#include "IfNode.h"
#include "ProcedureNode.h"
#include "StatementListNode.h"

using namespace std;

class TreeAnalyzer {
public:
	explicit TreeAnalyzer();
	~TreeAnalyzer();

	static SpaDataContainer* analyzeTree(Node* rootNode);

	map<int, vector<int>> analyzeParentsTable(Node* rootNode) const;
	void parentsTableProcedureWalker(map<int, vector<int>>& result, ProcedureNode* procedureNode) const;
	void parentsTableCheckValidParent(map<int, vector<int>>& result, Node* node) const;
	void parentsTableAddWhile(map<int, vector<int>>& result, WhileNode* whileNode) const;
	void parentsTableAddIf(map<int, vector<int>>& result, IfNode* ifNode) const;

	map<int, vector<int>> analyzeFollowsTable(Node* rootNode) const;
	void followsTableStatementListWalker(map<int, vector<int>>& result, StatementListNode* statementListNode) const;
	void followsTableCheckValidParent(map<int, vector<int>>& result, Node* node) const;
};
