#include "Next.h"
#include "AssignNode.h"
#include "WhileNode.h"
#include "IfNode.h"
#include "StatementListNode.h"
#include "CallNode.h"
#include "VariableNode.h"
#include "ProcedureNode.h"

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
		return inWhileNodeSearch(dynamic_cast<WhileNode*>(s1Node.front()), s2Node.front());
	}
	else if (dynamic_cast<IfNode*>(s1Node.front())) {
		return inIfNodeSearch(dynamic_cast<IfNode*>(s1Node.front()), s2Node.front());
	}
	else {
		return inProcedureSearch(s1Node.front(), s2Node.front());
			//s1Node.front()->getProgramLineNumber() + 1 == s2Node.front()->getProgramLineNumber();
	}	
}

bool Next::inIfNodeSearch(IfNode * ifNode, Node * nextNode)
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

bool Next::inWhileNodeSearch(WhileNode * whileNode, Node * nextNode)
{
	StatementListNode* whileStatement = dynamic_cast<StatementListNode*>(whileNode->getChild(1));
	Node* firstWhileNode = whileStatement->getChildren().front();
	
	if (whileNode->getProgramLineNumber() + 1 == nextNode->getProgramLineNumber() ||
		whileNode->getProgramLineNumber() + 1 == firstWhileNode->getProgramLineNumber()) {
		return true;
	}

	return false;
}

bool Next::inProcedureSearch(Node * firstNode, Node * secondNode)
{

	if (dynamic_cast<StatementListNode*>(firstNode->getParent()) && dynamic_cast<ProcedureNode*>(firstNode->getParent()->getParent()) == nullptr) {
		//sprawdzamy czy nie jest on ostatnim elementem steytemntListy
		StatementListNode* stmtNode = dynamic_cast<StatementListNode*>(firstNode->getParent());

		//first jest ostatni w stmtList
		if (stmtNode->getChildren().back()->getProgramLineNumber() == firstNode->getProgramLineNumber()) {
			if (dynamic_cast<WhileNode*>(firstNode->getParent()->getParent())) {
				WhileNode* currentWhileNode = dynamic_cast<WhileNode*>(firstNode->getParent()->getParent());
				return currentWhileNode->getProgramLineNumber() == secondNode->getProgramLineNumber();
			}
			else if (dynamic_cast<IfNode*>(firstNode->getParent()->getParent()))
			{
				IfNode* currentIfNode = dynamic_cast<IfNode*>(firstNode->getParent()->getParent());
				Node* nexttt = getNext(secondNode);
				Node* nesad = getNext(firstNode);
				return getNext(currentIfNode)->getProgramLineNumber() == secondNode->getProgramLineNumber();
			}
		}
		else
		{
			return firstNode->getProgramLineNumber() + 1 == secondNode->getProgramLineNumber();
		}
	}

	return firstNode->getProgramLineNumber() + 1 == secondNode->getProgramLineNumber();
}

Node * Next::getNext(Node * node)
{
	Node* parent = node->getParent();
	vector<Node*> children;

	if (dynamic_cast<StatementListNode*>(parent)) {
		children = parent->getParent()->getParent()->getChildren();
	}
	else
	{
		children = parent->getChildren();
	}

	for (int i = 0; i < children.size(); i++) {
		if (children[i]->getProgramLineNumber() == node->getProgramLineNumber() && i+1 <= children.size() - 1) {
			return children[i + 1];
		}
	}

	return node;
}

Node * Next::getNext2(Node * startNode, Node * s1, Node * s2)
{
	vector<Node*> children;

	if (dynamic_cast<StatementListNode*>(startNode->getParent())) {
		if (dynamic_cast<WhileNode*>(startNode->getParent()->getParent())) {

		}

		if (dynamic_cast<IfNode*>(startNode->getParent()->getParent())) {
			children = startNode->getChildren(); //pobranie wszystkich linni znajdujacych sie w if

			for (int i = 0; i < children.size(); i++) {
				if (children[i]->getProgramLineNumber() == s1->getProgramLineNumber() && i + 1 <= children.size() - 1) {
					return children[i + 1];
				}
			}
		}
	}

	return nullptr;
}



