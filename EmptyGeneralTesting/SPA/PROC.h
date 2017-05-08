#pragma once
#include <string>

using namespace std;

class PROC
{
private:
	string procName = "";

public:
	PROC();
	PROC(string procName);
	~PROC();
	void setProc(string procName);
	string getProc();
	bool operator==(PROC &proc) const;
};

