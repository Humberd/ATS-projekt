#pragma once
#include "ParameterType.h"
#include <string>

using namespace std;

class Parameter {
private:
	ParameterType type;
	string stringValue;
	int integerValue;

public:
	explicit Parameter(ParameterType type, string stringValue);
	explicit Parameter(ParameterType type, int integerValue);
	explicit Parameter(ParameterType type);
	~Parameter();


	ParameterType getType() const;
	void setType(const ParameterType type);
	string getStringValue() const;
	void setStringValue(const string stringValue);
	int getIntegerValue() const;
	void setIntegerValue(const int integerValue);
};

