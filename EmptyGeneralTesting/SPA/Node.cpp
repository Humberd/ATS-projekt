#include "Node.h"

using namespace std;

Node::Node() {
	
}

/**
 * Deletes only children, not a parent
 */
Node::~Node() {
	for (Node* child : this->children) {
		delete child;
	}
	this->children.clear();
}

vector<Node*> Node::getChildren() const {
	return this->children;
}

Node* Node::getChild(int index) const {
	return this->children.at(index);
}

void Node::setParent(Node* parent){
	this->parent = parent;
}

Node* Node::getParent() const{
	return this->parent;
}

void Node::_addChild(Node* child) {
	this->children.push_back(child);

	child->setParent(this);
}
