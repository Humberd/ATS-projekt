#include "FromCallDeepTraverser.h"

FromCallDeepTraverser::FromCallDeepTraverser(map<string, vector<PROC*>> table) : table(table) {
}

inline vector<PROC*> FromCallDeepTraverser::getProceduresFromCallsTable(PROC* p)
{
	vector<PROC*> returnList;

	for (map<string, vector<PROC*>>::iterator it = table.begin(); it != table.end(); ++it) {
		if (isCalls(it->first, p)) {
			returnList.push_back(new PROC(it->first));
		}
	}

	return returnList;
}

bool FromCallDeepTraverser::isGatheringListFull()
{
	return this->gatheringList.size() == table.size();
}

void FromCallDeepTraverser::addChildToGatheringList(PROC* p)
{
	this->gatheringList.insert(p->getProc());
}

vector<PROC*> FromCallDeepTraverser::filterAlreadyVisitedProcedures(vector<PROC*> children)
{
	vector<PROC*> filteredChildren;

	for (auto child : children) {
		if (gatheringList.count(child->getProc()) == 0) {
			filteredChildren.push_back(child);
		}
	}
	return filteredChildren;
}

void FromCallDeepTraverser::setTraverserTable(map<string, vector<PROC*>> table)
{
	this->table = table;
}

void FromCallDeepTraverser::traverse(PROC* parentProcedure)
{
	vector<PROC*> childrenProcedures = this->getProceduresFromCallsTable(parentProcedure);

	vector<PROC*> filteredProcedures = this->filterAlreadyVisitedProcedures(childrenProcedures);

	if (filteredProcedures.size() == 0) {
		return;
	}

	for (auto child : filteredProcedures) {
		this->addChildToGatheringList(child);
	}

	if (isGatheringListFull()) {
		return;
	}
	else
	{
		for (auto child : filteredProcedures) {
			this->traverse(child);

			if (isGatheringListFull()) {
				return;
			}
		}
	}
}

set<PROC*> FromCallDeepTraverser::getGatheringList()
{
	set<PROC*> returnList;

	for (string procName : this->gatheringList) {
		returnList.insert(new PROC(procName));
	}

	return returnList;
}

bool FromCallDeepTraverser::isCalls(string p, PROC* q)
{
	if (table.count(p) == 0)
	{
		return false;
	}
	else
	{
		for (PROC* t : table.at(p)) {
			if (t->getProc() == q->getProc()) {
				return true;
			}
		}

		return false;
	}
}