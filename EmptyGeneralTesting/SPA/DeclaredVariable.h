#pragma once
#include <string>

using namespace std;

class DeclaredVariable {
private:
	string type;
	string name;

public:
	explicit DeclaredVariable();
	explicit DeclaredVariable(string type, string name);
	~DeclaredVariable();

	string getType() const;
	void setType(const string type);
	string getName() const;
	void setName(const string name);
};
