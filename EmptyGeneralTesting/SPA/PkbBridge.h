#pragma once
#include <vector>

using namespace std;

class PkbBrigde {

public:
	explicit PkbBrigde();
	~PkbBrigde();

	vector<string> getChildrenOf(string statement, bool goDeep) const;
	vector<string> getParentOf(string statement, bool goDeep) const;
};
