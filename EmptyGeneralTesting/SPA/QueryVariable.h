#pragma once
#include <string>

using namespace std;

class QueryVariable {
private:
	string name;
	string propertyName;

public:
	explicit QueryVariable();
	~QueryVariable();


	string getName() const;
	void setName(const string name);
	string getPropertyName() const;
	void setPropertyName(const string propertyName);
};