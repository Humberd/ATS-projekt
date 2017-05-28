#pragma once
#include <vector>
#include "STMT.h"
#include "VAR.h"
#include "PROC.h"

using namespace std;

class PkbBrigde {

public:
	explicit PkbBrigde();
	virtual ~PkbBrigde();

	virtual vector<string> getChildrenOf(string statement, bool goDeep) const = 0;
	virtual vector<string> getParentOf(string statement, bool goDeep) const = 0;
	virtual bool isElemParentOf(string parent, string child, bool goDeep) const = 0;

	virtual vector<string> getFollowedBy(string statement, bool goDeep) const = 0;
	virtual vector<string> getPrevious(string statement, bool goDeep) const = 0;
	virtual bool isElemFollowing(string first, string next, bool goDeep) const = 0;

	virtual vector<string> getStatementsThatModifies(string variable) const = 0;
	virtual vector<string> getProceduresThatModifies(string variable) const = 0;
	virtual vector<string> getVariableThatIsModifiedByStatement(string statement) const = 0;
	virtual vector<string> getVariableThatIsModifiedByProcedure(string procedure) const = 0;
	virtual bool isStatementModifyingVariable(string statement, string variable) const = 0;
	virtual bool isProceduretModifyingVariable(string procedure, string variable) const = 0;

	STMT* parseStringToStmt(string statement) const;
	VAR* parseStringToVar(string variable) const;
	PROC* parceStringToProc(string procedure) const;

	vector<string> parseStmtsToStrings(vector<STMT*>& statements) const;
	vector<string> parseProceduresToStrings(vector<PROC*>& procedures) const;
	vector<string> parseVariablesToStrings(vector<VAR*>& variables) const;
};
