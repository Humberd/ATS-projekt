#include "../SPA/DeepTraverser.h"

template<class T>
inline vector<T> DeepTraverser<T>::getProceduresFromCallsTable(T p)
{
	if (table.count(p) == 1) {
		return table.at(p);
	}
	else {
		return vector<T>();
	}
}

template<class T>
bool DeepTraverser<T>::isGatheringListFull()
{
	return this->gatheringList.size() == this->table.size();
}

template<class T>
void DeepTraverser<T>::addChildToGatheringList(T p)
{
	this->gatheringList.insert(p);
}

template<class T>
vector<T> DeepTraverser<T>::filterAlreadyVisitedProcedures(vector<T> children)
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
void DeepTraverser<T>::setTraverserTable(map<T, vector<T>> table)
{
	this->table = table;
}

template<class T>
void DeepTraverser<T>::traverse(T parentProcedure)
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
set<T> DeepTraverser<T>::getGatheringList()
{
	return this->gatheringList;
}
