#pragma once
#include <vector>
#include "STMT.h"

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


	STMT* parseStringToStmt(string statement) const;
	vector<string> parseStmtsToStrings(vector<STMT*>& statements) const;

};
