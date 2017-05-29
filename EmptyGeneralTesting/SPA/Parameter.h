#pragma once
#include "ParameterType.h"
#include <string>

using namespace std;

class Parameter {
private:
	ParameterType type;
	string variableName;
	string variableType;
	string stringValue;
	int integerValue;

public:
	explicit Parameter();
	~Parameter();

	ParameterType getType() const;
	void setType(const ParameterType type);
	string getVariableName() const;
	void setVariableName(const string variableName);
	string getVariableType() const;
	void setVariableType(const string variableType);
	string getStringValue() const;
	void setStringValue(const string stringValue);
	int getIntegerValue() const;
	void setIntegerValue(const int integerValue);
};
