#pragma once
#include <string>
#include "Parameter.h"

using namespace std;

class MethodRequest {
private:
	string methodName;
	bool goDeep;
	Parameter* leftParam;
	Parameter* rightParam;

public:
	explicit MethodRequest();
	~MethodRequest();

	string getMethodName() const;
	void setMethodName(const string methodName);
	bool getGoDeep() const;
	void setGoDeep(const bool goDeep);
	Parameter* getLeftParam() const;
	void setLeftParam(Parameter* const leftParam);
	Parameter* getRightParam() const;
	void setRightParam(Parameter* const rightParam);
};
