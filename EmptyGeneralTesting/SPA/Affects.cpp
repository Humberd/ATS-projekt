#include "Affects.h"
#include "AssignNode.h"
#include "VariableNode.h"


Affects::Affects(SpaDataContainer* spaDataContainer, PkbBrigde* pkbBridge): spaDataContainer(spaDataContainer),pkbBridge(pkbBridge) {
}

vector<ASSIGN*> Affects::getAffects(ASSIGN* a, bool goDeep) {
	if (goDeep) {
		return getAffectsWithDeep(a);
	} else {
		return getAffectsWithoutDeep(a);
	}
}

vector<ASSIGN*> Affects::getAffectsBy(ASSIGN* a, bool goDeep) {
	if (goDeep) {
		return getAffectsByWithDeep(a);
	} else {
		return getAffectsByWithoutDeep(a);
	}
}

bool Affects::ifAffects(ASSIGN* a1, ASSIGN* a2, bool goDeep) {
	if (goDeep) {
		return ifAffectsWithDeep(a1, a2);
	} else {
		return ifAffectsWithoutDeep(a1, a2);
	}
}


vector<ASSIGN*> Affects::getAffectsWithoutDeep(ASSIGN* a) {
	vector<ASSIGN*> result;
//	string varName;

//	Node* startingNode = this->spaDataContainer->statementTable.at(a->getASSIGN()).at(0);
//	if (dynamic_cast<AssignNode*>(startingNode) != nullptr) {
//		varName = (dynamic_cast<VariableNode*>(startingNode->getChild(0))->getName());
//	} else {
//		return result;
//	}
//	vector<string> flowPaths = pkbBridge->getNextStatements(to_string(a->getASSIGN()), true);

	return result;
}

vector<ASSIGN*> Affects::getAffectsWithDeep(ASSIGN* a) {
	vector<ASSIGN*> result;


	return vector<ASSIGN*>();
}

vector<ASSIGN*> Affects::getAffectsByWithDeep(ASSIGN* a) {
	return vector<ASSIGN*>();
}

vector<ASSIGN*> Affects::getAffectsByWithoutDeep(ASSIGN* a) {
	return vector<ASSIGN*>();
}

bool Affects::ifAffectsWithoutDeep(ASSIGN* a1, ASSIGN* a2) {
	return false;
}

bool Affects::ifAffectsWithDeep(ASSIGN* a1, ASSIGN* a2) {
	return false;
}
