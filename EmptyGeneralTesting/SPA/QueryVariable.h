#pragma once
#include <string>

using namespace std;

class QueryVariable {
private:
	string name;
	string propertyName;
	string type;

public:
	explicit QueryVariable();
	explicit QueryVariable(string name, string propertyName);
	~QueryVariable();


	string getName() const;
	void setName(const string name);
	string getPropertyName() const;
	void setPropertyName(const string propertyName);
	string getType() const;
	void setType(const string type);
};