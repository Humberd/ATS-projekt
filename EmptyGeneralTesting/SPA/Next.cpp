#include "Next.h"
#include "AssignNode.h"
#include "WhileNode.h"
#include "IfNode.h"
#include "StatementListNode.h"
#include "CallNode.h"
#include "VariableNode.h"

Next *Next::instance = 0;

Next::Next(map<int, vector<Node*>> statementTable)
{
	this->statementTable = statementTable;
}

vector<STMT*> Next::goNext(STMT * s, bool goDeep)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goPrevious(STMT * s, bool goDeep)
{
	return vector<STMT*>();
}

bool Next::isNext(STMT * s1, STMT * s2, bool goDeep)
{
	return goDeep ? isNextDeep(s1, s2) : isNext(s1, s2);
}

Next * Next::getInstance(map<int, vector<Node*>> statementTable)
{
	if (!instance) {
		instance = new Next(statementTable);
	}

	return instance;
}

vector<STMT*> Next::goNextWithoutDeep(STMT * s)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goNextWithDeep(STMT * s)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goNextByWithDeep(STMT * s)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goNextByWithoutDeep(STMT * s)
{
	return vector<STMT*>();
}

bool Next::isNextDeep(STMT * s1, STMT * s2)
{
	return false;
}

bool Next::isNext(STMT * s1, STMT * s2)
{
	vector<Node*> s1Node = this->statementTable.at(s1->getSTMT());
	vector<Node*> s2Node = this->statementTable.at(s2->getSTMT());

	if (dynamic_cast<WhileNode*>(s1Node.front())) {
		return false;
	}
	else if (dynamic_cast<IfNode*>(s1Node.front())) {
		return inIfNode(dynamic_cast<IfNode*>(s1Node.front()), s2Node.front());
	}
	else {
		return s1Node.front()->getProgramLineNumber() + 1 == s2Node.front()->getProgramLineNumber();
	}	
}

bool Next::inIfNode(IfNode * ifNode, Node * nextNode)
{
	for (auto child : ifNode->getChildren()) {
		if (dynamic_cast<StatementListNode*>(child)) {
			auto stmtNode = dynamic_cast<StatementListNode*>(child);
			
			for (auto stmtChild : stmtNode->getChildren()) {
				if (stmtChild->getProgramLineNumber() == nextNode->getProgramLineNumber()) {
					return true;
				}
			}
		}
		else 
		{
			if (child->getProgramLineNumber() == nextNode->getProgramLineNumber()) {
				return true;
			}
		}
	}

	return false;
}



