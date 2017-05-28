#include <vector>
#include "STMT.h"
#include <map>
#include "IfNode.h"
#include "Node.h"
#include "WhileNode.h"

using namespace std;

class Next {

public:
	Next(map<int, vector<Node*>> statementTable);
	vector<STMT*> goNext(STMT* s, bool goDeep);
	vector<STMT*> goPrevious(STMT* s, bool goDeep);
	bool isNext(STMT* s1, STMT* s2, bool goDeep);
	static Next *getInstance(map<int, vector<Node*>> statementTable);
private:
	static Next *instance;
	map<int, vector<Node*>> statementTable;
	vector<STMT*> goNextWithoutDeep(STMT* s);
	vector<STMT*> goNextWithDeep(STMT* s);
	vector<STMT*> goNextByWithDeep(STMT* s);
	vector<STMT*> goNextByWithoutDeep(STMT* s);
	bool isNextDeep(STMT* s1, STMT* s2);
	bool isNext(STMT* s1, STMT* s2);
	bool inIfNodeSearch(IfNode* ifNode, Node* nextNode);
	bool inWhileNodeSearch(WhileNode* whileNode, Node* nextNode);
	bool inProcedureSearch(Node* firstNode, Node* secondNode);
	Node* getNext(Node* node);
	Node* getNext2(Node* startNode, Node* s1, Node* s2);
	Node * getNext2Deep(Node * startNode, Node * s2, vector<Node*>& imHere);
};