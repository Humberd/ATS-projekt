#pragma once

#include <vector>
#include <set>
#include <map>
#include "PROC.h"

using namespace std;

class FromCallDeepTraverser {
private:
	map<string, vector<PROC*>> table;
	set<string> gatheringList;

	vector<PROC*> getProceduresFromCallsTable(PROC* p);
	bool isGatheringListFull();
	void addChildToGatheringList(PROC* p);
	vector<PROC*> filterAlreadyVisitedProcedures(vector<PROC*> children);
	bool isCalls(string p, PROC* q);
public:
	void setTraverserTable(map<string, vector<PROC*>> table);
	explicit FromCallDeepTraverser(map<string, vector<PROC*>> table);

	void traverse(PROC* parentProcedure);
	set<PROC*> getGatheringList();
};
