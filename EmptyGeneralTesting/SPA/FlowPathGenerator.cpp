#include "FlowPathGenerator.h"
#include "AssignNode.h"
#include "WhileNode.h"
#include "CallNode.h"
#include "IfNode.h"

FlowPathGenerator::FlowPathGenerator() {
}

FlowPathGenerator::~FlowPathGenerator() {
}

void FlowPathGenerator::generateFlowPath(SpaDataContainer* spaDataContainer) {
	vector<NodeFlowWrapper*> proceduresFlowWrappers;
	map<int, NodeFlowWrapper*> flowWrappersTable;

	for (auto procedureNode : spaDataContainer->proceduresTable) {
		NodeFlowWrapper* nodeFlowWrapper = new NodeFlowWrapper(procedureNode);
		flowStatementList(nodeFlowWrapper, procedureNode->getChild(0), flowWrappersTable);
		proceduresFlowWrappers.push_back(nodeFlowWrapper);
	}

	spaDataContainer->proceduresFlowWrappers = proceduresFlowWrappers;
	spaDataContainer->flowWrappersTable = flowWrappersTable;

}

void FlowPathGenerator::flowStatementList(NodeFlowWrapper* parentFlowWrapper, Node* statementListNode, map<int, NodeFlowWrapper*>& globalTable) {
	NodeFlowWrapper* currentParentWrapper = parentFlowWrapper;
	for (auto childNode : statementListNode->getChildren()) {
		currentParentWrapper = flowSingleStatement(currentParentWrapper, childNode, globalTable);
	}

	/*If while loop, then make it loop*/
	if (dynamic_cast<WhileNode*>(parentFlowWrapper->getNode()) != nullptr) {
		parentFlowWrapper->addPathIntoNode(currentParentWrapper);
		currentParentWrapper->addPathOutOfNode(parentFlowWrapper);
	}
}

NodeFlowWrapper* FlowPathGenerator::flowSingleStatement(NodeFlowWrapper* parentFlowWrapper, Node* currentNode, map<int, NodeFlowWrapper*>& globalTable) {
	NodeFlowWrapper* nodeFlowWrapper = new NodeFlowWrapper(currentNode);
	parentFlowWrapper->addPathOutOfNode(nodeFlowWrapper);
	nodeFlowWrapper->addPathIntoNode(parentFlowWrapper);

	globalTable.insert_or_assign(currentNode->getProgramLineNumber(), nodeFlowWrapper);

	if (dynamic_cast<AssignNode*>(currentNode) != nullptr) {
		return nodeFlowWrapper;
	}

	if (dynamic_cast<CallNode*>(currentNode) != nullptr) {
		return nodeFlowWrapper;
	}

	if (dynamic_cast<WhileNode*>(currentNode) != nullptr) {
		flowStatementList(nodeFlowWrapper, currentNode->getChild(1), globalTable);
		return nodeFlowWrapper;
	}

	if (dynamic_cast<IfNode*>(currentNode) != nullptr) {
		flowStatementList(nodeFlowWrapper, currentNode->getChild(1), globalTable);
		flowStatementList(nodeFlowWrapper, currentNode->getChild(2), globalTable);
		return nodeFlowWrapper;
	}
}

