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

vector<string> PkbBridgeMockImpl::getStatementsThatModifies(string variable) const {
	return vector<string>{"4"};
}

vector<string> PkbBridgeMockImpl::getProceduresThatModifies(string variable) const {
	return vector<string>{"v,x,y"};
}

vector<string> PkbBridgeMockImpl::getVariableThatIsModifiedByStatement(string statement) const {
	return vector<string>{"e"};
}

vector<string> PkbBridgeMockImpl::getVariableThatIsModifiedByProcedure(string procedure) const {
	return vector<string>{"f"};
}

bool PkbBridgeMockImpl::isStatementModifyingVariable(string statement, string variable) const {
	return true;
}

bool PkbBridgeMockImpl::isProceduretModifyingVariable(string procedure, string variable) const {
	return true;
}

vector<string> PkbBridgeMockImpl::getVariablesUsedByStatement(string statement) const {
	return vector<string>{"f"};
}

vector<string> PkbBridgeMockImpl::getVariablesUsedByProcedure(string procedure) const {
	return vector<string>{"f","g"};
}

vector<string> PkbBridgeMockImpl::getStatementsThatUses(string variable) const {
	return vector<string>{"2"};
}

vector<string> PkbBridgeMockImpl::getProceduresThatUses(string variable) const {
	return vector<string>{"Earth"};
}

bool PkbBridgeMockImpl::isStatementUsingVariable(string statement, string variable) const {
	return true;
}

bool PkbBridgeMockImpl::isProcedureUsingVariable(string procedure, string variable) const {
	return true;
}


vector<string> PkbBridgeMockImpl::getProceduresThatAreCalledBy(string procedure, bool doDeep) const {
	return vector<string>{"Earth"};
}

vector<string> PkbBridgeMockImpl::getProceduresThatCalls(string procedure, bool goDeep) const {
	return vector<string>{"Earth"};
}

bool PkbBridgeMockImpl::isProcedureCalling(string procedureCalling, string procedureCalled, bool goDeep) const {
	return true;
}

vector<string> PkbBridgeMockImpl::getNextStatements(string statement, bool goDeep) const {
	return vector<string>{"1"};
}

vector<string> PkbBridgeMockImpl::getBeforeStatements(string statement, bool goDeep) const {
	return vector<string>{"1"};
}

bool PkbBridgeMockImpl::isStatmentBeforeNext(string statementBefore, string statementNext, bool goDeep) const {
	return true;
}
