#include "CallsNode.h"

CallsNode::CallsNode(PROC proc) : Node(1, new RangeNumber(INT32_MIN, INT32_MAX))
{
	this->proc = proc;
}

CallsNode::~CallsNode()
{
}

void CallsNode::setProc(PROC proc)
{
	this->proc = proc;
}

PROC CallsNode::getProc() const
{
	return this->proc;
}

void CallsNode::addChild(Node * child)
{
	this->_addChild(child);
}

void CallsNode::addChildren(vector<PROC> children)
{
	for (PROC proc : children) {
		this->addChild(new CallsNode(proc));
	}
}
