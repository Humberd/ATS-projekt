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
		vector<NodeFlowWrapper*> nodeFlowWrapper{new NodeFlowWrapper(procedureNode)};
		flowStatementList(nodeFlowWrapper, procedureNode->getChild(0), flowWrappersTable);
		proceduresFlowWrappers.insert(proceduresFlowWrappers.end(), nodeFlowWrapper.begin(), nodeFlowWrapper.end());
	}

	spaDataContainer->proceduresFlowWrappers = proceduresFlowWrappers;
	spaDataContainer->flowWrappersTable = flowWrappersTable;

}

vector<NodeFlowWrapper*> FlowPathGenerator::flowStatementList(vector<NodeFlowWrapper*>& parentFlowWrappers, Node* statementListNode, map<int, NodeFlowWrapper*>& globalTable) {
	vector<NodeFlowWrapper*> currentParentWrappers = parentFlowWrappers;
	for (auto childNode : statementListNode->getChildren()) {
		currentParentWrappers = flowSingleStatement(currentParentWrappers, childNode, globalTable);
	}

	/*If while loop, then make it loop*/
	for (auto parentFlowWrapper : parentFlowWrappers) {
		if (dynamic_cast<WhileNode*>(parentFlowWrapper->getNode()) != nullptr) {
			for (auto currentParentWrapper : currentParentWrappers) {
				parentFlowWrapper->addPathIntoNode(currentParentWrapper);
				currentParentWrapper->addPathOutOfNode(parentFlowWrapper);
			}
		}
	}

	return currentParentWrappers;
}

vector<NodeFlowWrapper*> FlowPathGenerator::flowSingleStatement(vector<NodeFlowWrapper*>& parentFlowWrappers, Node* currentNode, map<int, NodeFlowWrapper*>& globalTable) {
	NodeFlowWrapper* nodeFlowWrapper = new NodeFlowWrapper(currentNode);
	globalTable.insert_or_assign(currentNode->getProgramLineNumber(), nodeFlowWrapper);

	for (auto parentFlowWrapper : parentFlowWrappers) {
		parentFlowWrapper->addPathOutOfNode(nodeFlowWrapper);
		nodeFlowWrapper->addPathIntoNode(parentFlowWrapper);
	}

	vector<NodeFlowWrapper*> newParrentWrappers{nodeFlowWrapper};
	if (dynamic_cast<AssignNode*>(currentNode) != nullptr) {
		return newParrentWrappers;
	}

	if (dynamic_cast<CallNode*>(currentNode) != nullptr) {
		return newParrentWrappers;
	}

	if (dynamic_cast<WhileNode*>(currentNode) != nullptr) {
		flowStatementList(newParrentWrappers, currentNode->getChild(1), globalTable);
		return newParrentWrappers;
	}

	if (dynamic_cast<IfNode*>(currentNode) != nullptr) {
		auto thenCallbacks = flowStatementList(newParrentWrappers, currentNode->getChild(1), globalTable);
		auto elseCallbacks = flowStatementList(newParrentWrappers, currentNode->getChild(2), globalTable);
		newParrentWrappers.clear();
		newParrentWrappers.insert(newParrentWrappers.end(), thenCallbacks.begin(), thenCallbacks.end());
		newParrentWrappers.insert(newParrentWrappers.end(), elseCallbacks.begin(), elseCallbacks.end());
		return newParrentWrappers;
	}
}
