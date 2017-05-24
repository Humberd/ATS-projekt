#pragma once
#include "ResponseState.h"
#include <vector>

using namespace std;

class MethodEvaluatorResponse {
private:
	ResponseState state;
	vector<string> vectorResponse;
	bool booleanResponse;
	string variableName;
	string variableType;

public:
	explicit MethodEvaluatorResponse();
	~MethodEvaluatorResponse();

	ResponseState getState() const;
	void setState(const ResponseState state);
	vector<string> getVectorResponse() const;
	void setVectorResponse(const vector<string> basicStrings);
	bool getBooleanResponse() const;
	void setBooleanResponse(const bool booleanResponse);
	string getVariableName() const;
	void setVariableName(const string variableName);
	string getVariableType() const;
	void setVariableType(const string variableType);
};
