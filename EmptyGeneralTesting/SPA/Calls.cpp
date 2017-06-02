#include "Calls.h"
#include <algorithm>
#include <set>
#include "../SPA/GetCallsDeepTraverser.h"
#include "../SPA/FromCallDeepTraverser.h"


Calls::Calls(map<string, vector<string>>& callsTable) {

	for (map<string, vector<string>>::const_iterator it = callsTable.begin(); it != callsTable.end(); ++it) {
		vector<PROC*> tmp;

		for (string value : callsTable.at(it->first)) {
			tmp.push_back(new PROC(value));
		}

		this->callsTable.insert(pair<string, vector<PROC*>>(it->first, tmp));
	}
}

Calls::~Calls() {

}

vector<PROC*> Calls::getCalls(PROC* p) {
	return callsTable.at(p->getProc());
}

vector<PROC*> Calls::getCallsDeep(PROC* p) {
	GetCallsDeepTraverser* traverser = new GetCallsDeepTraverser(callsTable);
	//traverser->setTraverserTable(callsTable);

	traverser->traverse(p);

	set<PROC*> resultSet = traverser->getGatheringList();

	/*Zamieniam set na vector*/
	vector<PROC*> resultVec(resultSet.begin(), resultSet.end());

	//delete traverser;

	return resultVec;
}

vector<PROC*> Calls::getCallsFrom(PROC* p) {
	vector<PROC*> returnCallsList;

	for (map<string, vector<PROC*>>::const_iterator it = callsTable.begin(); it != callsTable.end(); ++it) {
		if (isCalls(it->first, p)) {
			returnCallsList.push_back(new PROC(it->first));
		}
	}

	return returnCallsList;
}

vector<PROC*> Calls::getCallsDeepFrom(PROC* p) {
	FromCallDeepTraverser* traverser = new FromCallDeepTraverser(callsTable);
	//traverser->setTraverserTable(callsTable);

	traverser->traverse(p);

	set<PROC*> resultSet = traverser->getGatheringList();

	/*Zamieniam set na vector*/
	vector<PROC*> resultVec(resultSet.begin(), resultSet.end());

	delete traverser;

	return resultVec;
}

void Calls::setCalls(PROC* p, PROC* q) {
	if (callsTable.count(p->getProc()) == 0) {
		vector<PROC*> tmp;
		tmp.push_back(q);
		callsTable.insert(pair<string, vector<PROC*>>(p->getProc(), tmp));
	} else {
		callsTable.at(p->getProc()).push_back(q);
	}
}

vector<PROC*> Calls::getCalls(PROC* p, bool goDeep) {
	return goDeep ? getCallsDeep(p) : getCalls(p);
}

vector<PROC*> Calls::getCallsFrom(PROC* q, bool goDeep) {
	return goDeep ? getCallsDeepFrom(q) : getCallsFrom(q);
}

bool Calls::isCalls(string p, PROC* q) {
	if (callsTable.count(p) == 0) {
		return false;
	} else {
		for (PROC* proc : callsTable.at(p)) {
			if (proc->getProc() == q->getProc()) {
				return true;
			}
		}

		return false;
	}
}
