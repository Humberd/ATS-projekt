#include "Node.h"
#include "ValidateException.h"
#include <cassert>
#include "InvalidArgumentException.h"

using namespace std;

Node::Node(int lineNumber, RangeNumber* rangeOfRequiredChildNodes) {
	if (lineNumber < 1) {
		throw InvalidArgumentException(this, "lineNumber must be a positive integer, but instead is: " + to_string(1));
	}
	if (rangeOfRequiredChildNodes == nullptr) {
		throw InvalidArgumentException(this, "rangeOfRequiredChildNodes must not be a null");
	}

	this->lineNumber = lineNumber;
	this->rangeOfRequiredChildNodes = rangeOfRequiredChildNodes;
}

Node::~Node() {
	startedDeleting = true;

	for (auto child : this->children) {
		if (!child->isStartedDeleting()) {
			delete child;
		}
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
		throw ValidateException(this, "Node is in a loop");
	}
	this->startedValidating = true;

	/*If the number of children is not in range of the range provided in a constructor*/
	if (!this->rangeOfRequiredChildNodes->isWithinRangeInclusive(this->getChildren().size())) {
		throw ValidateException(this, "Node requires to have a number of children between "
			+ to_string(this->rangeOfRequiredChildNodes->getMin()) + " and "
			+ to_string(this->rangeOfRequiredChildNodes->getMax()) + ", but instead got: "
			+ to_string(this->getChildren().size()));
	}

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

bool Node::isStartedDeleting() const {
	return this->startedDeleting;
}
