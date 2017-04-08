#pragma once
#include <vector>

using namespace std;

class Node {
protected:
	vector<Node*> children;
	Node* parent = nullptr;

	Node();

public:
	virtual ~Node() = 0;

	virtual void addChild(Node* child) = 0;
	vector<Node*> getChildren() const;
	Node* getChild(int index) const;

	void setParent(Node* parent);
	Node* getParent() const;

	//sprawdzam, ze wszystkie nody, maja wymagana liczbe dzieci
	virtual void validate() = 0;
};
