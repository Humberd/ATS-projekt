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
	vector<Node*> s1Node = this->statementTable.at(s1->getSTMT());
	vector<Node*> s2Node = this->statementTable.at(s2->getSTMT());
	vector<Node*> imHere;
	if (getNext2Deep(s1Node.front(), s2Node.front(), imHere) != nullptr) return true;

	return false;
}

bool Next::isNext(STMT * s1, STMT * s2)
{
	vector<Node*> s1Node = this->statementTable.at(s1->getSTMT());
	vector<Node*> s2Node = this->statementTable.at(s2->getSTMT());

	Node* aa = getNext2(s1Node.front(), s1Node.front(), s2Node.front());

	if (aa != nullptr && aa->getProgramLineNumber() == s2Node.front()->getProgramLineNumber()) {
		return true;
	}
	else
	{
		return false;
	}

	//if (dynamic_cast<WhileNode*>(s1Node.front())) {
	//	return inWhileNodeSearch(dynamic_cast<WhileNode*>(s1Node.front()), s2Node.front());
	//}
	//else if (dynamic_cast<IfNode*>(s1Node.front())) {
	//	return inIfNodeSearch(dynamic_cast<IfNode*>(s1Node.front()), s2Node.front());
	//}
	//else {
	//	return inProcedureSearch(s1Node.front(), s2Node.front());
	//		//s1Node.front()->getProgramLineNumber() + 1 == s2Node.front()->getProgramLineNumber();
	//}	
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

	if (dynamic_cast<StatementListNode*>(startNode->getParent()) && dynamic_cast<ProcedureNode*>(startNode->getParent()->getParent()) == nullptr) {
		if (dynamic_cast<WhileNode*>(startNode->getParent()->getParent())) {
			for (auto child : startNode->getParent()->getParent()->getChildren()) {
				if (dynamic_cast<StatementListNode*>(child)) {
					auto stmtNode = dynamic_cast<StatementListNode*>(child);

					if (stmtNode->getChildren().back()->getProgramLineNumber() == s1->getProgramLineNumber()) //sprawdzam czy wyrazenie jest ostatnie w stmt list
					{
						return child->getParent();
					}

					for (int i = 0; i < stmtNode->getChildren().size(); i++) {
						if (stmtNode->getChildren()[i]->getProgramLineNumber() == s1->getProgramLineNumber() && i + 1 <= stmtNode->getChildren().size() - 1) {
							return stmtNode->getChildren()[i + 1];
						}
					}
				}
			}
		}

		if (dynamic_cast<IfNode*>(startNode->getParent()->getParent())) {
			children = startNode->getParent()->getChildren(); //pobranie wszystkich linni znajdujacych sie w if

			for (auto child : startNode->getParent()->getParent()->getChildren()) {
				if (dynamic_cast<StatementListNode*>(child)) {
					auto stmtNode = dynamic_cast<StatementListNode*>(child);

					if (stmtNode->getChildren().back()->getProgramLineNumber() == s1->getProgramLineNumber()) //sprawdzam czy wyrazenie jest ostatnie w stmt list
					{
						return getNext2(startNode->getParent()->getParent(), startNode->getParent()->getParent(), s2);
					}

					for (int i = 0; i < stmtNode->getChildren().size(); i++) {
						if (stmtNode->getChildren()[i]->getProgramLineNumber() == s1->getProgramLineNumber() && i + 1 <= stmtNode->getChildren().size() - 1) {
							return stmtNode->getChildren()[i + 1];
						}
					}
				}
			}
		}
	}
	else
	{
		if (dynamic_cast<IfNode*>(startNode))
		{
			children = startNode->getChildren();

			for (auto child : children) {
				if (dynamic_cast<StatementListNode*>(child)) {
					auto stmtNode = dynamic_cast<StatementListNode*>(child);

					for (int i = 0; i < stmtNode->getChildren().size(); i++) {
						if (stmtNode->getChildren()[i]->getProgramLineNumber() == s2->getProgramLineNumber()) {
							return s2;
						}
					}
				}
			}

			return nullptr;
		}

			for (int i = 0; i < startNode->getParent()->getChildren().size(); i++) {
				if (startNode->getParent()->getChildren()[i]->getProgramLineNumber() == s1->getProgramLineNumber() && i + 1 <= startNode->getParent()->getChildren().size() - 1) {
					return startNode->getParent()->getChildren()[i + 1];
				}
			}
		
	}



	return nullptr;
}

Node * Next::getNext2Deep(Node * startNode, Node * s2, vector<Node*>& imHere)
{
	bool omg = false;
	int counter = 0;

	for (Node* node : imHere) {
		if (node->getProgramLineNumber() == startNode->getProgramLineNumber()) {
			omg = true;
			counter++;
		}
	}

	if (dynamic_cast<StatementListNode*>(startNode->getParent()) && dynamic_cast<ProcedureNode*>(startNode->getParent()->getParent()) == nullptr && omg == false) {
		if (dynamic_cast<WhileNode*>(startNode->getParent()->getParent())) {
			for (auto child : startNode->getParent()->getParent()->getChildren()) {
				if (dynamic_cast<StatementListNode*>(child)) {
					auto stmtNode = dynamic_cast<StatementListNode*>(child);

					for (Node* child : stmtNode->getChildren()) {

						if (child->getProgramLineNumber() == s2->getProgramLineNumber()) {
							return s2;
						}

						if (dynamic_cast<WhileNode*>(child) || dynamic_cast<IfNode*>(child)) {
							imHere.push_back(child);
							getNext2Deep(child, s2, imHere);
						}
					}
				}
			}
			return getNext2Deep(startNode->getParent()->getParent(), s2, imHere);
		}

		if (dynamic_cast<IfNode*>(startNode->getParent()->getParent())) {
			for (auto child : startNode->getParent()->getParent()->getChildren()) {
				if (dynamic_cast<StatementListNode*>(child)) {
					auto stmtNode = dynamic_cast<StatementListNode*>(child);

					for (Node* child : stmtNode->getChildren()) {

						if (child->getProgramLineNumber() == s2->getProgramLineNumber()) {
							return s2;
						}

						if (dynamic_cast<WhileNode*>(child) || dynamic_cast<IfNode*>(child)) {
							imHere.push_back(child);
							getNext2Deep(child, s2, imHere);
						}
					}
				}
			}

			return getNext2Deep(startNode->getParent()->getParent(), s2, imHere);
		}
	}
	else if (counter < 20)
	{
		if (dynamic_cast<IfNode*>(startNode))
		{
			for (auto child : startNode->getChildren()) {
				if (dynamic_cast<StatementListNode*>(child)) {
					auto stmtNode = dynamic_cast<StatementListNode*>(child);

					for (int i = 0; i < stmtNode->getChildren().size(); i++) {
						if (stmtNode->getChildren()[i]->getProgramLineNumber() == s2->getProgramLineNumber()) {
							return s2;
						}
					}

					if (dynamic_cast<WhileNode*>(child) || dynamic_cast<IfNode*>(child)) {
						imHere.push_back(child);
						return getNext2Deep(child, s2, imHere);
					}
				}
			}
		}

		if (dynamic_cast<WhileNode*>(startNode)) {
			for (auto child : startNode->getChildren()) {
				if (dynamic_cast<StatementListNode*>(child)) {
					auto stmtNode = dynamic_cast<StatementListNode*>(child);

					for (Node* child : stmtNode->getChildren()) {

						if (child->getProgramLineNumber() == s2->getProgramLineNumber()) {
							return s2;
						}

						if (dynamic_cast<WhileNode*>(child) || dynamic_cast<IfNode*>(child)) {
							imHere.push_back(child);
							return getNext2Deep(child, s2, imHere);
						}
					}
				}
			}
		}

		for (int i = 0; i < startNode->getParent()->getChildren().size(); i++) {
			if (startNode->getParent()->getChildren()[i]->getProgramLineNumber() == s2->getProgramLineNumber() && i + 1 <= startNode->getParent()->getChildren().size() - 1) {
				return s2;
			}

			if (dynamic_cast<WhileNode*>(startNode->getParent()->getChildren()[i]) || dynamic_cast<IfNode*>(startNode->getParent()->getChildren()[i])) {
				imHere.push_back(startNode->getParent()->getChildren()[i]);
				return getNext2Deep(startNode->getParent()->getChildren()[i], s2, imHere);
			}
		}
	}

	return nullptr;
}
