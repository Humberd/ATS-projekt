#pragma once
#include <string>

using namespace std;

class QueryMethods {
private:
	QueryMethods();
	~QueryMethods();

public:
	static const string PARENT;
	static const string FOLLOWS;
	static const string USES;
	static const string CALLS;
	static const string NEXT;
	static const string MODIFIES;
	static const string AFFECTS;
	static const string PATTERN;

	static bool isQueryMethod(string value);
};