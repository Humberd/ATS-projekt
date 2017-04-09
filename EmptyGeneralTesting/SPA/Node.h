#pragma once
#include <vector>

using namespace std;

class Node {
private:
	/*A list of children nodes*/
	vector<Node*> children;
	/*A parent node*/
	Node* parent = nullptr;
	/*A line number in the program of a node*/
	int lineNumber;

protected:
	/*Initialize a node with the line number*/
	explicit Node(int lineNumber);

	/*Adding a child and setting this object as its parent*/
	void _addChild(Node* child);
	/*Need to check if there is no loops when traversing a tree
	 * and if there is a required number of children nodes
	 */
	void _validate();

public:
	/*Making this class abstract*/
	virtual ~Node() = 0;

	/*Getting a list of children Nodes*/
	vector<Node*> getChildren() const;
	/*Getting a specific child Node*/
	Node* getChild(int index) const;

	/*Setting a parent Node*/
	void setParent(Node* parent);
	/*Getting a parent Node*/
	Node* getParent() const;

	//sprawdzam, ze wszystkie nody, maja wymagana liczbe dzieci
	virtual void validate() = 0;

	virtual void addChild(Node* child) = 0;

};
