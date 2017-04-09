#pragma once
#include "../SPA/Constants.h"
#include <vector>

using namespace std;

class NodePKBT {
private:
	vector<NodePKBT*> children;
	NodePKBT* parent;

protected:
	NodePKBT();

public:
	virtual ~NodePKBT() = 0;

	virtual void addChild(NodePKBT *child);
	vector<NodePKBT*> getChildren();
	NodePKBT* getChild(int index);

	void setParent(NodePKBT* parent);
	NodePKBT* getParent();
};