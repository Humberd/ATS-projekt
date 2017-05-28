#pragma once
#include "PkbBridge.h"
#include "SpaDataContainer.h"
#include "Parent.h"
#include "Follows.h"

class PkbBridgeImpl: public PkbBrigde {
	Parent* parentApi;
	Follows* followsApi;

public:
	explicit PkbBridgeImpl(SpaDataContainer* spaDataContainer);
	~PkbBridgeImpl() override;
	vector<string> getChildrenOf(string statement, bool goDeep) const override;
	vector<string> getParentOf(string statement, bool goDeep) const override;
	bool isElemParentOf(string parent, string child, bool goDeep) const override;

	vector<string> getFollowedBy(string statement, bool goDeep) const override;
	vector<string> getPrevious(string statement, bool goDeep) const override;
	bool isElemFollowing(string first, string next, bool goDeep) const override;
};
