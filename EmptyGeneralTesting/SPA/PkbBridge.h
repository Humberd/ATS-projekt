#pragma once
#include <vector>

using namespace std;

class PkbBrigde {

public:
	explicit PkbBrigde();
	~PkbBrigde();

	vector<int> getChildrenOf(int statement, bool goDeep) const;
	vector<int> getParentOf(int statement, bool goDeep) const;
};
