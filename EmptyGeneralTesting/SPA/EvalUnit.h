#pragma once
#include "EvalUnitType.h"
#include <string>

using namespace std;

class EvalUnit {
private:
	EvalUnitType type;
	int integerValue;
	string stringValue;

	string variableName;

public:
	explicit EvalUnit();
	~EvalUnit();

	EvalUnitType getType() const;
	void setType(const EvalUnitType type);
	int getIntegerValue() const;
	void setIntegerValue(const int integerValue);
	string getStringValue() const;
	void setStringValue(const string stringValue);
	string getVariableName() const;
	void setVariableName(const string variableName);
};
