#pragma once
#include <vector>
#include <map>
#include "PROC.h"

using namespace std;

class Calls
{
private:
	map<string, vector<PROC*>> callsTable;
	static Calls *instance;

	vector<PROC*> getCalls(PROC* p);
	vector<PROC*> getCallsDeep(PROC* p);
	vector<PROC*> getCallsFrom(PROC* p);
	vector<PROC*> getCallsDeepFrom(PROC* p);

public:
	static Calls *getInstance(map<string, vector<string>> callsTable);
	Calls(map<string, vector<string>> callsTable);
	~Calls();
	void setCalls(PROC* p, PROC* q);
	vector<PROC*> getCalls(PROC* p, bool goDeep);	
	vector<PROC*> getCallsFrom(PROC* q, bool goDeep);
	bool isCalls(string p, PROC* q);

};
