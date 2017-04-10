#include "../SPA/FromDeepTraverser.h"

template<class T>
inline vector<T> FromDeepTraverser<T>::getProceduresFromCallsTable(T p)
{
	vector<T> returnList;

	for (map<T, vector<T>>::iterator it = table.begin(); it != table.end(); ++it) {
		if (isCalls(it->first, p)) {
			returnList.push_back(it->first);
		}
	}

	return returnList;
}

template<class T>
bool FromDeepTraverser<T>::isGatheringListFull()
{
	return this->gatheringList.size() == this->table.size();
}

template<class T>
void FromDeepTraverser<T>::addChildToGatheringList(T p)
{
	this->gatheringList.insert(p);
}

template<class T>
vector<T> FromDeepTraverser<T>::filterAlreadyVisitedProcedures(vector<T> children)
{
	vector<T> filteredChildren;

	for (auto child : children) {
		if (gatheringList.count(child) == 0) {
			filteredChildren.push_back(child);
		}
	}
	return filteredChildren;
}

template<class T>
void FromDeepTraverser<T>::setTraverserTable(map<T, vector<T>> table)
{
	this->table = table;
}

template<class T>
void FromDeepTraverser<T>::traverse(T parentProcedure)
{
	vector<T> childrenProcedures = this->getProceduresFromCallsTable(parentProcedure);

	vector<T> filteredProcedures = this->filterAlreadyVisitedProcedures(childrenProcedures);

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

template<class T>
set<T> FromDeepTraverser<T>::getGatheringList()
{
	return this->gatheringList;
}

template<class T>
bool FromDeepTraverser<T>::isCalls(T p, T q)
{
	if (table.count(p) == 0)
	{
		return false;
	}
	else
	{
		for (T t : table[p]) {
			if (t == q) {
				return true;
			}
		}

		return false;
	}
}