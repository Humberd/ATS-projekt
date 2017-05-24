#include "PkbBridge.h"


PkbBrigde::PkbBrigde() {
}

PkbBrigde::~PkbBrigde() {
}

vector<int> PkbBrigde::getChildrenOf(int statement, bool goDeep) const {
	vector<int> result = {8,9,10,11};
	return result;
}

vector<int> PkbBrigde::getParentOf(int statement, bool goDeep) const {
	vector<int> result = {4};
	return result;
}
