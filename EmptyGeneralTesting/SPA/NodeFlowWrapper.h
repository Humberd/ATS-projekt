#pragma once
#include "Node.h"

class NodeFlowWrapper {
private:
	Node* node;
	vector<NodeFlowWrapper*> pathsIntoNode;
	vector<NodeFlowWrapper*> pathsOutOfNode;

public:
	explicit NodeFlowWrapper(Node* node);
	~NodeFlowWrapper();

	Node* getNode() const;
	vector<NodeFlowWrapper*> getPathsIntoNode() const;
	void addPathIntoNode(NodeFlowWrapper* nodeFlowWrapper);
	vector<NodeFlowWrapper*> getPathsOutOfNode() const;
	void addPathOutOfNode(NodeFlowWrapper* nodeFlowWrapper);
};
