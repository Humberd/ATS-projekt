#pragma once
#include <vector>
#include "NodeFlowWrapper.h"
#include "SpaDataContainer.h"

using namespace std;

class FlowPathGenerator {
public:
	explicit FlowPathGenerator();
	~FlowPathGenerator();

	/*Each NodeFlowWrapper has a procedure as a starting node*/
	static void generateFlowPath(SpaDataContainer* spaDataContainer);
	static void flowStatementList(NodeFlowWrapper* parentFlowWrapper, Node* statementListNode, map<int, NodeFlowWrapper*>& globalTable);
	static NodeFlowWrapper* flowSingleStatement(NodeFlowWrapper* parentFlowWrapper, Node* currentNode, map<int, NodeFlowWrapper*>& globalTable);

};
