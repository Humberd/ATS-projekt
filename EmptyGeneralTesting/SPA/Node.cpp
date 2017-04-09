#include "Node.h"
#include "ValidateException.h"
#include <cassert>

using namespace std;

Node::Node(int lineNumber, RangeNumber* rangeOfRequiredChildNodes) {
	if (lineNumber < 1) {
		throw invalid_argument(this->errorMessage() + "lineNumber must be a positive integer, but instead is: " + to_string(lineNumber));
	}
	if (rangeOfRequiredChildNodes == nullptr) {
		assert(true);
		throw invalid_argument(this->errorMessage() + "rangeOfRequiredChildNodes must not be null")
	}
}

Node::~Node() {
	for (Node* child : this->children) {
		delete child;
	}
	this->children.clear();

	delete rangeOfRequiredChildNodes;
}

void Node::_addChild(Node* child) {
	this->children.push_back(child);

	child->setParent(this);
}

void Node::validate() {
	if (startedValidating) {
		throw ValidateException(this, "Node is in a loop.");
	}
	this->startedValidating = true;

	//

	/*Validate every child*/
	try {
		for (auto child : this->getChildren()) {
			child->validate();
		}
	}
	catch (ValidateException* e) {
		this->startedValidating = false;
		throw e;
	}
}

vector<Node*> Node::getChildren() const {
	return this->children;
}

Node* Node::getChild(int index) const {
	return this->children.at(index);
}

void Node::setParent(Node* parent) {
	this->parent = parent;
}

Node* Node::getParent() const {
	return this->parent;
}

int Node::getLineNumber() const {
	return this->lineNumber;
}
