#include "NodeFlowWrapper.h"

NodeFlowWrapper::NodeFlowWrapper(Node* node) : node(node) {
}

NodeFlowWrapper::~NodeFlowWrapper() {
}

Node* NodeFlowWrapper::getNode() const {
	return node;
}

vector<NodeFlowWrapper*> NodeFlowWrapper::getPathsIntoNode() const {
	return pathsIntoNode;
}

vector<NodeFlowWrapper*> NodeFlowWrapper::getPathsOutOfNode() const {
	return pathsOutOfNode;
}

void NodeFlowWrapper::addPathIntoNode(NodeFlowWrapper* nodeFlowWrapper) {
	this->pathsIntoNode.push_back(nodeFlowWrapper);
}

void NodeFlowWrapper::addPathOutOfNode(NodeFlowWrapper* nodeFlowWrapper) {
	this->pathsOutOfNode.push_back(nodeFlowWrapper);
}
