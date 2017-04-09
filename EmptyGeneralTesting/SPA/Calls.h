#pragma once
#include "Constants.h"
#include <vector>
#include <map>

using namespace std;

class Calls
{
private:
	map<PROC, vector<PROC>> callsTable;
	static Calls *instance;

	Calls();

	vector<PROC> getCalls(PROC p);
	vector<PROC> getCallsDeep(PROC p);
	vector<PROC> getCallsFrom(PROC p);
	vector<PROC> getCallsDeepFrom(PROC p);

public:
	static Calls *getInstance();
	~Calls();
	void setCalls(PROC p, PROC q);
	vector<PROC> getCalls(PROC p, bool goDeep);	
	vector<PROC> getCallsFrom(PROC q, bool goDeep);
	bool isCalls(PROC p, PROC q);

};
