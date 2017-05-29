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
	static vector<NodeFlowWrapper*> flowStatementList(vector<NodeFlowWrapper*>& parentFlowWrappers, Node* statementListNode, map<int, NodeFlowWrapper*>& globalTable);
	static vector<NodeFlowWrapper*> flowSingleStatement(vector<NodeFlowWrapper*>& parentFlowWrappers, Node* currentNode, map<int, NodeFlowWrapper*>& globalTable);

};
