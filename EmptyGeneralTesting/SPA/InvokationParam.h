#pragma once
#include <string>
#include "ValueType.h"
#include "InvokationParamState.h"

using namespace std;

class InvokationParam {
private:
	string value;
	ValueType valueType;

	InvokationParamState state;

	string variableName;

public:
	explicit InvokationParam();
	~InvokationParam();

	string getValue() const;
	void setValue(const string value);
	ValueType getValueType() const;
	void setValueType(const ValueType valueType);
	InvokationParamState getState() const;
	void setState(const InvokationParamState state);
	string getVariableName() const;
	void setVariableName(const string variableName);

	InvokationParam* copy() const;
};
