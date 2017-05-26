#pragma once
#include <vector>

using namespace std;

class PkbBrigde {

public:
	explicit PkbBrigde();
	virtual ~PkbBrigde();

	virtual vector<string> getChildrenOf(string statement, bool goDeep) const = 0;
	virtual vector<string> getParentOf(string statement, bool goDeep) const = 0;
	virtual bool isElemParentOf(string parent, string child, bool goDeep) const = 0;
};
