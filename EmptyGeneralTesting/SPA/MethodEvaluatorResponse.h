#pragma once
#include "ResponseState.h"
#include <vector>

using namespace std;

class MethodEvaluatorResponse {
private:
	bool booleanResponse;
	ResponseState state;
	vector<string> vectorResponse;
	string variableName;
	string variableType;

	string insertToColumnName;
	string insertToColumnValue;

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
	string getInsertToColumnName() const;
	void setInsertToColumnName(const string insertToColumnName);
	string getInsertToColumnValue() const;
	void setInsertToColumnValue(const string insertToColumnValue);
};
