#include "Node.h"
#include "ValidateException.h"
#include "InvalidArgumentException.h"
//#include <CppUnitTestLogger.h>
#include <sstream>
#include <CppUnitTestLogger.h>

//#include <CppUnitTestLogger.h>


using namespace std;

Node::Node(int sourceLineNumber,
           RangeNumber* rangeOfRequiredChildNodes) {
	if (sourceLineNumber < 1) {
		throw InvalidArgumentException(this, "sourceLineNumber must be a positive integer, but instead is: " + to_string(sourceLineNumber));
	}
	if (rangeOfRequiredChildNodes == nullptr) {
		throw InvalidArgumentException(this, "rangeOfRequiredChildNodes must not be a null");
	}

	this->sourceLineNumber = sourceLineNumber;
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
	} catch (ValidateException&) {
		this->startedValidating = false;
		throw;
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

int Node::getSourceLineNumber() const {
	return sourceLineNumber;
}

void Node::setProgramLineNumber(int programLineNumber) {
	this->programLineNumber = programLineNumber;
}

int Node::getProgramLineNumber() const {
	return programLineNumber;
}

bool Node::isStartedDeleting() const {
	return this->startedDeleting;
}

string Node::getClassName() const {
	return string(typeid(*this).name());
}

void Node::prettyPrint(int indent) {
	stringstream ss;

	for (int i = 0; i < indent; i++) {
		ss << "|  ";
	}
	ss << toString();

	Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(ss.str().c_str());

	for (auto child : children) {
		child->prettyPrint(indent + 1);
	}
}

void Node::prettyPrint() {
	prettyPrint(0);
}

string Node::toString() const {
	return getClassName() + "(" + to_string(sourceLineNumber) + ", " + to_string(programLineNumber) + ")";
}
