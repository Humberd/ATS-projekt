#include "PkbBridgeMockImpl.h"

PkbBridgeMockImpl::PkbBridgeMockImpl() {
}

PkbBridgeMockImpl::~PkbBridgeMockImpl() {
}

vector<string> PkbBridgeMockImpl::getChildrenOf(string statement, bool goDeep) const {
	return vector<string>{"8", "9", "10", "11"};
}

vector<string> PkbBridgeMockImpl::getParentOf(string statement, bool goDeep) const {
	return vector<string>{"4"};
}

bool PkbBridgeMockImpl::isElemParentOf(string parent, string child, bool goDeep) const {
	return true;
}


vector<string> PkbBridgeMockImpl::getFollowedBy(string statement, bool goDeep) const {
	return vector<string>{"3"};
}

vector<string> PkbBridgeMockImpl::getPrevious(string statement, bool goDeep) const {
	return vector<string>{"2"};
}

bool PkbBridgeMockImpl::isElemFollowing(string first, string next, bool goDeep) const {
	return true;
}
