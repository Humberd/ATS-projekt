#pragma once
#include <vector>
#include "Affects.h"
#include <set>
#include <map>
#include "PROC.h"

class CallsNode;
using namespace std;

class GetCallsDeepTraverser {
private:
	map<string, vector<PROC*>> callsTable;
	set<string> gatheringList;

	vector<PROC*> getProceduresFromCallsTable(PROC* p);
	bool isGatheringListFull();
	void addChildToGatheringList(PROC* p);
	vector<PROC*> filterAlreadyVisitedProcedures(vector<PROC*> children);
	
public:
	explicit GetCallsDeepTraverser(map<string, vector<PROC*>> callsTable);

	void traverse(PROC* parentProcedure);
	set<PROC*> getGatheringList();
};
