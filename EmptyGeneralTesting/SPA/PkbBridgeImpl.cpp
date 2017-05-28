#include "PkbBridgeImpl.h"

PkbBridgeImpl::PkbBridgeImpl(SpaDataContainer* spaDataContainer) {
	parentApi = new Parent(spaDataContainer->parentsTable, spaDataContainer->statementTable);
	followsApi = new Follows(spaDataContainer->followsTable);
}

PkbBridgeImpl::~PkbBridgeImpl() {
	delete parentApi;
	delete followsApi;
}

vector<string> PkbBridgeImpl::getChildrenOf(string statement, bool goDeep) const {
	vector<STMT*> rawResponse = parentApi->getParent(parseStringToStmt(statement), goDeep);
	return parseStmtsToStrings(rawResponse);
}

vector<string> PkbBridgeImpl::getParentOf(string statement, bool goDeep) const {
	vector<STMT*> rawResponse = parentApi->getParentOf(parseStringToStmt(statement), goDeep);
	return parseStmtsToStrings(rawResponse);
}

bool PkbBridgeImpl::isElemParentOf(string parent, string child, bool goDeep) const {
	bool response = parentApi->isParent(parseStringToStmt(parent), parseStringToStmt(child), goDeep);
	return response;
}

vector<string> PkbBridgeImpl::getFollowedBy(string statement, bool goDeep) const {
	vector<STMT*> rawResponse = followsApi->getFollows(parseStringToStmt(statement), goDeep);
	return parseStmtsToStrings(rawResponse);
}

vector<string> PkbBridgeImpl::getPrevious(string statement, bool goDeep) const {
	vector<STMT*> rawResponse = followsApi->getFollowsBy(parseStringToStmt(statement), goDeep);
	return parseStmtsToStrings(rawResponse);
}

bool PkbBridgeImpl::isElemFollowing(string first, string next, bool goDeep) const {
	bool response = followsApi->isFollows(parseStringToStmt(first), parseStringToStmt(next), goDeep);
	return response;
}
