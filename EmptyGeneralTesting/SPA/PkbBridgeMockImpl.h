#pragma once
#include "PkbBridge.h"

class PkbBridgeMockImpl: public PkbBrigde {

public:
	explicit PkbBridgeMockImpl();
	~PkbBridgeMockImpl() override;
	
	vector<string> getChildrenOf(string statement, bool goDeep) const override;
	vector<string> getParentOf(string statement, bool goDeep) const override;
	bool isElemParentOf(string parent, string child, bool goDeep) const override;
};
