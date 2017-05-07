#pragma once
#include <vector>
#include "RangeNumber.h"

using namespace std;

class Node {
private:
	/*A list of children nodes*/
	vector<Node*> children;
	/*A parent node*/
	Node* parent = nullptr;
	/*A line, which the Node exists in a source file*/
	int sourceLineNumber;
	/*A sourceline, but without counting: procedure declarations, empty lanes and else statements*/
	int programLineNumber;

	RangeNumber* rangeOfRequiredChildNodes = nullptr;

	/*Helper variable to check if the tree is not looping - used by validate() method*/
	bool startedValidating = false;
	/*Helper variable to check if the tree deletion is not looping - used by destuctors*/
	bool startedDeleting = false;

protected:
	/*Initialize a node with the line number*/
	explicit Node(int sourceLineNumber, RangeNumber* rangeOfRequiredChildNodes);

	/*Adding a child and setting this object as its parent*/
	void _addChild(Node* child);

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

	/*Getting a source line number*/
	int getSourceLineNumber() const;

	/*Setting a program line number*/
	void setProgramLineNumber(int programLineNumber);
	/*Getting a program line number*/
	int getProgramLineNumber() const;

	/*Gets the name of the class, for example: "class VariableNode"*/
	string getClassName() const;

	virtual string toString() const;

	/*Prints all the node details and its children*/
	void prettyPrint(int indent);
	void prettyPrint();

	/*Need to check if there is no loops when traversing a tree
	* and if there is a required number of children nodes
	*/
	virtual void validate();

	virtual void addChild(Node* child) = 0;

	//////////////////////
	bool isStartedDeleting() const;
};
