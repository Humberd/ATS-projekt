#pragma once
#include <vector>
#include "Affects.h"
#include <set>
#include <map>

class CallsNode;
using namespace std;

class GetCallsDeepTraverser {
private:
	map<PROC, vector<PROC>> callsTable;
	set<PROC> gatheringList;

	vector<PROC> getProceduresFromCallsTable(PROC p);
	bool isGatheringListFull();
	void addChildToGatheringList(PROC p);
	vector<PROC> filterAlreadyVisitedProcedures(vector<PROC> children);
	
public:
	explicit GetCallsDeepTraverser(map<PROC, vector<PROC>> callsTable);

	void traverse(PROC parentProcedure);
	set<PROC> getGatheringList();
};
