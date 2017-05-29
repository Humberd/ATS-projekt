#include "Next.h"
#include "WhileNode.h"
#include "IfNode.h"
#include "StatementListNode.h"
#include "ProcedureNode.h"
#include <algorithm>


Next::Next(SpaDataContainer* spaDataContainer) : spaDataContainer(spaDataContainer) {
}

vector<STMT*> Next::goNext(STMT* s, bool goDeep) {
	if (goDeep) {
		return goNextWithDeep(s);
	} else {
		return goNextWithoutDeep(s);
	}
}

vector<STMT*> Next::goBefore(STMT* s, bool goDeep) {
	if (goDeep) {
		return goBeforeWithDeep(s);
	} else {
		return goBeforeWithoutDeep(s);
	}
}

bool Next::isNext(STMT* s1, STMT* s2, bool goDeep) {
	if (goDeep) {
		return isNextWithDeep(s1, s2);
	} else {
		return isNextWithoutDeep(s1, s2);
	}
}

vector<STMT*> Next::goNextWithoutDeep(STMT* s) {
	vector<STMT*> result;

	NodeFlowWrapper* nodeWrapper;
	try {
		nodeWrapper = spaDataContainer->flowWrappersTable.at(s->getSTMT());
	} catch (out_of_range&) {
		return result;
	}

	for (auto nextWrapper : nodeWrapper->getPathsOutOfNode()) {
		result.push_back(new STMT(nextWrapper->getNode()->getProgramLineNumber()));
	}

	delete s;

	return result;
}

vector<STMT*> Next::goNextWithDeep(STMT* s) {
	vector<STMT*> response;
	vector<NodeFlowWrapper*> alreadyBeenToSpecialNodes;
	bool firstNode = true;

	goNextWithDeepSingle(spaDataContainer->flowWrappersTable.at(s->getSTMT()), response, alreadyBeenToSpecialNodes, firstNode);

	delete s;

	return response;
}

void Next::goNextWithDeepSingle(NodeFlowWrapper* currentNode, vector<STMT*>& response, vector<NodeFlowWrapper*>& alreadyBeenToSpecialNodes, bool& firstNode) {
	/*If I've already been to this node*/
	if (any_of(alreadyBeenToSpecialNodes.begin(), alreadyBeenToSpecialNodes.end(),
	           [currentNode](NodeFlowWrapper* beenBeforeNode) {
		           return beenBeforeNode == currentNode;
	           })) {
		return;
	}

	if (firstNode && currentNode->getPathsOutOfNode().size() == 0) {
		return;
	}
	firstNode &= false;

	if (dynamic_cast<WhileNode*>(currentNode->getNode()) != nullptr) {
		alreadyBeenToSpecialNodes.push_back(currentNode);
	} else if (dynamic_cast<IfNode*>(currentNode->getNode()) != nullptr) {
		alreadyBeenToSpecialNodes.push_back(currentNode);
	}

	response.push_back(new STMT(currentNode->getNode()->getProgramLineNumber()));

	for (auto pathsIntoNode : currentNode->getPathsOutOfNode()) {
		goNextWithDeepSingle(pathsIntoNode, response, alreadyBeenToSpecialNodes, firstNode);
	}
}

vector<STMT*> Next::goBeforeWithoutDeep(STMT* s) {
	vector<STMT*> result;

	NodeFlowWrapper* nodeWrapper;
	try {
		nodeWrapper = spaDataContainer->flowWrappersTable.at(s->getSTMT());
	} catch (out_of_range&) {
		return result;
	}

	for (auto beforeWrapper : nodeWrapper->getPathsIntoNode()) {
		if (dynamic_cast<ProcedureNode*>(beforeWrapper->getNode()) != nullptr) {
			break;
		}

		result.push_back(new STMT(beforeWrapper->getNode()->getProgramLineNumber()));
	}

	delete s;

	return result;
}

vector<STMT*> Next::goBeforeWithDeep(STMT* s) {
	vector<STMT*> response;
	vector<NodeFlowWrapper*> alreadyBeenToSpecialNodes;
	bool firstNode = true;

	goBeforeWithDeepSingle(spaDataContainer->flowWrappersTable.at(s->getSTMT()), response, alreadyBeenToSpecialNodes, firstNode);

	delete s;

	return response;
}

void Next::goBeforeWithDeepSingle(NodeFlowWrapper* currentNode, vector<STMT*>& response, vector<NodeFlowWrapper*>& alreadyBeenToSpecialNodes, bool& firstNode) {
	/*If I've already been to this node*/
	if (any_of(alreadyBeenToSpecialNodes.begin(), alreadyBeenToSpecialNodes.end(),
	           [currentNode](NodeFlowWrapper* beenBeforeNode) {
		           return beenBeforeNode == currentNode;
	           })) {
		return;
	}
	if (firstNode && dynamic_cast<ProcedureNode*>(currentNode->getPathsIntoNode().at(0)->getNode()) != nullptr) {
		return;
	}
	firstNode &= false;

	/*Reached already a head of a procedure*/
	if (dynamic_cast<ProcedureNode*>(currentNode->getNode()) != nullptr) {
		return;
	}

	if (dynamic_cast<WhileNode*>(currentNode->getNode()) != nullptr) {
		alreadyBeenToSpecialNodes.push_back(currentNode);
	} else if (dynamic_cast<IfNode*>(currentNode->getNode()) != nullptr) {
		alreadyBeenToSpecialNodes.push_back(currentNode);
	}

	response.push_back(new STMT(currentNode->getNode()->getProgramLineNumber()));

	for (auto pathsIntoNode : currentNode->getPathsIntoNode()) {
		goBeforeWithDeepSingle(pathsIntoNode, response, alreadyBeenToSpecialNodes, firstNode);
	}
}

bool Next::isNextWithoutDeep(STMT* s1, STMT* s2) {
	NodeFlowWrapper* nodeWrapper;
	try {
		nodeWrapper = spaDataContainer->flowWrappersTable.at(s1->getSTMT());
	} catch (out_of_range&) {
		return false;
	}

	auto outPaths = nodeWrapper->getPathsOutOfNode();

	bool result = any_of(outPaths.begin(), outPaths.end(),
	                     [s2](NodeFlowWrapper* nextWrapper) {
		                     return nextWrapper->getNode()->getProgramLineNumber() == s2->getSTMT();
	                     });

	delete s1 , s2;

	return result;
}

bool Next::isNextWithDeep(STMT* s1, STMT* s2) {
	NodeFlowWrapper* nodeWrapper;
	try {
		nodeWrapper = spaDataContainer->flowWrappersTable.at(s1->getSTMT());
	} catch (out_of_range&) {
		return false;
	}

	vector<NodeFlowWrapper*> alreadyBeenToSpecialNodes;
	bool found = false;
	bool firstChild = true;
	int wantedProgramLine = s2->getSTMT();

	isNextWithDeepSingle(nodeWrapper, found, wantedProgramLine, alreadyBeenToSpecialNodes, firstChild);

	delete s1, s2;

	return found;
}

void Next::isNextWithDeepSingle(NodeFlowWrapper* currentNode, bool& found, int& wantedProgramLine, vector<NodeFlowWrapper*>& alreadyBeenToSpecialNodes, bool& firstNode) {
	/*If I've already been to this node*/
	if (any_of(alreadyBeenToSpecialNodes.begin(), alreadyBeenToSpecialNodes.end(),
		[currentNode](NodeFlowWrapper* beenBeforeNode) {
		return beenBeforeNode == currentNode;
	})) {
		return;
	}

	if (firstNode && currentNode->getPathsOutOfNode().size() == 0) {
		return;
	}
	firstNode &= false;

	if (dynamic_cast<WhileNode*>(currentNode->getNode()) != nullptr) {
		alreadyBeenToSpecialNodes.push_back(currentNode);
	} else if (dynamic_cast<IfNode*>(currentNode->getNode()) != nullptr) {
		alreadyBeenToSpecialNodes.push_back(currentNode);
	}

	if (currentNode->getNode()->getProgramLineNumber() == wantedProgramLine) {
		found = true;
		return;
	}

	for (auto pathsIntoNode : currentNode->getPathsOutOfNode()) {
		isNextWithDeepSingle(pathsIntoNode, found, wantedProgramLine, alreadyBeenToSpecialNodes, firstNode);
		if (found) {
			return;
		}
	}

}
