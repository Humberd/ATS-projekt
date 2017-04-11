#include "Calls.h"
#include <algorithm>
#include <set>
#include "GetCallsDeepTraverser.h"

#include "../SPA/DeepTraverser.h"
#include "../SPA/DeepTraverser.cpp"
#include "../SPA/FromDeepTraverser.h"
#include "../SPA/FromDeepTraverser.cpp"

Calls *Calls::instance = 0;

Calls::Calls()
{

}

Calls::~Calls()
{

}

vector<PROC> Calls::getCalls(PROC p)
{
	return callsTable[p];
}

vector<PROC> Calls::getCallsDeep(PROC p)
{
	DeepTraverser<PROC>* traverser = new DeepTraverser<PROC>();
	traverser->setTraverserTable(callsTable);

	traverser->traverse(p);

	set<PROC> resultSet = traverser->getGatheringList();

	/*Zamieniam set na vector*/
	vector<PROC> resultVec(resultSet.begin(), resultSet.end());

	delete traverser;

	return resultVec;
}

vector<PROC> Calls::getCallsFrom(PROC p)
{
	vector<PROC> returnCallsList;

	for (map<PROC, vector<PROC>>::iterator it = callsTable.begin(); it != callsTable.end(); ++it) {
		if (isCalls(it->first, p)) {
			returnCallsList.push_back(it->first);
		}
	}

	return returnCallsList;
}

vector<PROC> Calls::getCallsDeepFrom(PROC p)
{
	FromDeepTraverser<PROC>* traverser = new FromDeepTraverser<PROC>();
	traverser->setTraverserTable(callsTable);

	traverser->traverse(p);

	set<PROC> resultSet = traverser->getGatheringList();

	/*Zamieniam set na vector*/
	vector<PROC> resultVec(resultSet.begin(), resultSet.end());

	delete traverser;

	return resultVec;
}

Calls *Calls::getInstance()
{
	if (!instance) {
		instance = new Calls();
	}

	return instance;
}

void Calls::setCalls(PROC p, PROC q)
{
	callsTable[p].push_back(q);
}

vector<PROC> Calls::getCalls(PROC p, bool goDeep)
{
	return goDeep ? getCallsDeep(p) : getCalls(p);
}

vector<PROC> Calls::getCallsFrom(PROC q, bool goDeep)
{
	return goDeep ? getCallsDeepFrom(q) : getCallsFrom(q);
}

bool Calls::isCalls(PROC p, PROC q)
{
	if (callsTable.count(p) == 0)
	{
		return false;
	}
	else
	{
		for (PROC proc : callsTable[p]) {
			if (proc == q) {
				return true;
			}
		}

		return false;
	}
}