#pragma once
#include <string>

using namespace std;

class Operators {
private:
	Operators();
	~Operators();

public:
	static const string PLUS_SIGN;
	static const string MINUS_SIGN;
	static const string TIMES_SIGN;

	static bool isOperator(string value);
	static bool isOperator(char value);
};