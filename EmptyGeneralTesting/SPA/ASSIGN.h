#pragma once
#include <string>

using namespace std;

class ASSIGN
{
private:
	int assign;

public:
	ASSIGN();
	ASSIGN(int assign);
	~ASSIGN();
	void setASSIGN(int assign);
	int getASSIGN();
	bool operator==(ASSIGN &rassign) const;
};

