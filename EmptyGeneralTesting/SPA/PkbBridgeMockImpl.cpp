#include "PkbBridgeMockImpl.h"

PkbBridgeMockImpl::PkbBridgeMockImpl() {
}

PkbBridgeMockImpl::~PkbBridgeMockImpl() {
}

vector<string> PkbBridgeMockImpl::getChildrenOf(string statement, bool goDeep) const {
	vector<string> result = {"8","9","10","11"};
	return result;
}

vector<string> PkbBridgeMockImpl::getParentOf(string statement, bool goDeep) const {
	vector<string> result = {"4"};
	return result;
}

bool PkbBridgeMockImpl::isElemParentOf(string parent, string child, bool goDeep) const {
	return true;
}
