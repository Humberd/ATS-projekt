#pragma once
#include <string>

using namespace std;

class VAR
{
private:
	string varName = "";

public:
	VAR();
	VAR(string varName);
	~VAR();
	void setVAR(string varName);
	string getVAR();
	bool operator==(VAR &var) const;
};

