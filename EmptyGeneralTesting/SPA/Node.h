#pragma once
#include <vector>

using namespace std;

class Node {
private:
	vector<Node*> children;
	Node* parent;

protected:
	Node();

public:
	virtual ~Node() = 0;

	virtual void addChild(Node* child) = 0;
	vector<Node*> getChildren();
	Node* getChild(int index);

	void setParent(Node* parent);
	Node* getParent();

	//sprawdzam, ze wszystkie nody, maja wymagana liczbe dzieci
	virtual void validate() = 0;
};
