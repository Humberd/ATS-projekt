#include "PkbBridgeImpl.h"

PkbBridgeImpl::PkbBridgeImpl(SpaDataContainer* spaDataContainer) {
	parentApi = new Parent(spaDataContainer->parentsTable, spaDataContainer->statementTable);
	followsApi = new Follows(spaDataContainer->followsTable);
	modifiesApi = new Modifies(spaDataContainer->modifiesStatementTable, spaDataContainer->modifiesProcedureTable);
//	usesApi = new Uses();
}

PkbBridgeImpl::~PkbBridgeImpl() {
	delete parentApi;
	delete followsApi;
	delete modifiesApi;
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

vector<string> PkbBridgeImpl::getStatementsThatModifies(string variable) const {
	vector<STMT*> rawResponse = modifiesApi->getModifiesSTMT(parseStringToVar(variable));
	return parseStmtsToStrings(rawResponse);

}

vector<string> PkbBridgeImpl::getProceduresThatModifies(string variable) const {
	vector<PROC*> rawResponse = modifiesApi->getModifiesPROC(parseStringToVar(variable));
	return parseProceduresToStrings(rawResponse);
}

vector<string> PkbBridgeImpl::getVariableThatIsModifiedByStatement(string statement) const {
	vector<VAR*> rawResponse = modifiesApi->getModifiesBy(parseStringToStmt(statement));
	return parseVariablesToStrings(rawResponse);
}

vector<string> PkbBridgeImpl::getVariableThatIsModifiedByProcedure(string procedure) const {
	vector<VAR*> rawResponse = modifiesApi->getModifiesBy(parceStringToProc(procedure));
	return parseVariablesToStrings(rawResponse);
}

bool PkbBridgeImpl::isStatementModifyingVariable(string statement, string variable) const {
	return modifiesApi->isModifies(stoi(statement), parseStringToVar(variable));
}

bool PkbBridgeImpl::isProceduretModifyingVariable(string procedure, string variable) const {
	return modifiesApi->isModifies(procedure, parseStringToVar(variable));
}

vector<string> PkbBridgeImpl::getVariablesUsedByStatement(string statement) const {
	vector<VAR*> rawResponse = usesApi->getUses(parseStringToStmt(statement));
	return parseVariablesToStrings(rawResponse);
}

vector<string> PkbBridgeImpl::getVariablesUsedByProcedure(string procedure) const {
	vector<VAR*> rawResponse = usesApi->getUses(parceStringToProc(procedure));
	return parseVariablesToStrings(rawResponse);
}

vector<string> PkbBridgeImpl::getStatementsThatUses(string variable) const {
	vector<STMT*> rawResponse = usesApi->getUsesBySTMT(parseStringToVar(variable));
	return parseStmtsToStrings(rawResponse);
}

vector<string> PkbBridgeImpl::getProceduresThatUses(string variable) const {
	vector<PROC*> rawResponse = usesApi->getUsesByPROC(parseStringToVar(variable));
	return parseProceduresToStrings(rawResponse);
}

bool PkbBridgeImpl::isStatementUsingVariable(string statement, string variable) const {
	return usesApi->isUsed(parseStringToStmt(statement), parseStringToVar(variable));
}

bool PkbBridgeImpl::isProcedureUsingVariable(string procedure, string variable) const {
	return usesApi->isUsed(parceStringToProc(procedure), parseStringToVar(variable));
}
