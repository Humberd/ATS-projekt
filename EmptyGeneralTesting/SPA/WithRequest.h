#pragma once
#include "QueryVariable.h"
#include "WithType.h"

class WithRequest {
private:
	WithType type;
	QueryVariable* leftSideVariable;
	QueryVariable* rightSideVariable;
	int rightSideInteger;
	string rightSideString;

public:
	explicit WithRequest();
	~WithRequest();

	WithType getType() const;
	void setType(const WithType type);
	QueryVariable* getLeftSideVariable() const;
	void setLeftSideVariable(QueryVariable* const leftSideVariable);
	QueryVariable* getRightSideVariable() const;
	void setRightSideVariable(QueryVariable* const rightSideVariable);
	int getRightSideInteger() const;
	void setRightSideInteger(const int rightSideInteger);
	string getRightSideString() const;
	void setRightSideString(const string rightSideString);
};
