#pragma once
#include <string>

using namespace std;

class DeclaredVariable {
private:
	string type;
	string name;

public:
	explicit DeclaredVariable(string type, string name);
	~DeclaredVariable();


	string getType() const;
	string getName() const;
};
