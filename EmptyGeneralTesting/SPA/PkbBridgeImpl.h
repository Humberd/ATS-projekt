#pragma once
#include "PkbBridge.h"
#include "SpaDataContainer.h"
#include "Parent.h"
#include "Follows.h"
#include "Modifies.h"
#include "Uses.h"
#include "Calls.h"
#include "Next.h"
#include "Affects.h"

class PkbBridgeImpl: public PkbBrigde {
	Parent* parentApi;
	Follows* followsApi;
	Modifies* modifiesApi;
	Uses* usesApi;
	Next* nextApi;
	Calls* callsApi;
	Affects* affectsApi;

public:
	explicit PkbBridgeImpl(SpaDataContainer* spaDataContainer);
	~PkbBridgeImpl() override;
	vector<string> getChildrenOf(string statement, bool goDeep) const override;
	vector<string> getParentOf(string statement, bool goDeep) const override;
	bool isElemParentOf(string parent, string child, bool goDeep) const override;

	vector<string> getFollowedBy(string statement, bool goDeep) const override;
	vector<string> getPrevious(string statement, bool goDeep) const override;
	bool isElemFollowing(string first, string next, bool goDeep) const override;

	vector<string> getStatementsThatModifies(string variable) const override;
	vector<string> getProceduresThatModifies(string variable) const override;
	vector<string> getVariableThatIsModifiedByStatement(string statement) const override;
	vector<string> getVariableThatIsModifiedByProcedure(string procedure) const override;
	bool isStatementModifyingVariable(string statement, string variable) const override;
	bool isProceduretModifyingVariable(string procedure, string variable) const override;

	vector<string> getVariablesUsedByStatement(string statement) const override;
	vector<string> getVariablesUsedByProcedure(string procedure) const override;
	vector<string> getStatementsThatUses(string variable) const override;
	vector<string> getProceduresThatUses(string variable) const override;
	bool isStatementUsingVariable(string statement, string variable) const override;
	bool isProcedureUsingVariable(string procedure, string variable) const override;

	vector<string> getProceduresThatAreCalledBy(string procedure, bool doDeep) const override;
	vector<string> getProceduresThatCalls(string procedure, bool goDeep) const override;
	bool isProcedureCalling(string procedureCalling, string procedureCalled, bool goDeep) const override;

	vector<string> getNextStatements(string statement, bool goDeep) const override;
	vector<string> getBeforeStatements(string statement, bool goDeep) const override;
	bool isStatmentBeforeNext(string statementBefore, string statementNext, bool goDeep) const override;

	vector<string> getAffectedStatements(string statement, bool goDeep) const override;
	vector<string> getAffectedStatementsBy(string statement, bool goDeep) const override;
	bool isStatmentAffectedBy(string statementBefore, string statementNext, bool goDeep) const override;
};
