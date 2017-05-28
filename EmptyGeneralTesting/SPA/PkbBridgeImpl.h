#pragma once
#include "PkbBridge.h"
#include "SpaDataContainer.h"
#include "Parent.h"
#include "Follows.h"
#include "Modifies.h"
#include "Uses.h"

class PkbBridgeImpl: public PkbBrigde {
	Parent* parentApi;
	Follows* followsApi;
	Modifies* modifiesApi;
	Uses* usesApi;

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
};
