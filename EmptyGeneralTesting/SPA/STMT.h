#pragma once
#include <string>

using namespace std;

class STMT
{
private:
	int stmt;

public:
	STMT();
	STMT(int stmt);
	~STMT();
	void setSTMT(int stmt);
	int getSTMT();
	bool operator==(STMT &rstmt) const;
};

