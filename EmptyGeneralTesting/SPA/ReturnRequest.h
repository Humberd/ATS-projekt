#pragma once
#include "ReturnType.h"
#include <vector>

using namespace std;

class ReturnRequest {
private:
	ReturnType returnType;
	string variableName;
	vector<string> toupleVariableNames;

public:
	explicit ReturnRequest();
	~ReturnRequest();

	ReturnType getReturnType() const;
	void setReturnType(const ReturnType returnType);
	string getVariableName() const;
	void setVariableName(const string variableName);
	vector<string> getToupleVariableNames() const;
	void setToupleVariableNames(const vector<string> toupleVariableNames);
};
