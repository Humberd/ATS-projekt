#pragma once

#include <vector>
#include <set>
#include <map>

using namespace std;

template <class T> 
class DeepTraverser {
private:
	map<T, vector<T>> table;
	set<T> gatheringList;
	
	vector<T> getProceduresFromCallsTable(T p);
	bool isGatheringListFull();
	void addChildToGatheringList(T p);
	vector<T> filterAlreadyVisitedProcedures(vector<T> children);
	
public:
	void setTraverserTable(map<T, vector<T>> table);
	
	void traverse(T parentProcedure);
	set<T> getGatheringList();
};
