#include "PkbBridge.h"


PkbBrigde::PkbBrigde() {
}

PkbBrigde::~PkbBrigde() {
}

vector<string> PkbBrigde::getChildrenOf(string statement, bool goDeep) const {
	vector<string> result = {"8","9","10","11"};
	return result;
}

vector<string> PkbBrigde::getParentOf(string statement, bool goDeep) const {
	vector<string> result = {"4"};
	return result;
}
