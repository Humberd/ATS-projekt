#pragma once
#include <string>

using namespace std;

class TokenKeys {
private:
	TokenKeys();
	~TokenKeys();

public:
	static const string KEYWORD;
	static const string NAME;
	static const string INTEGER;
	static const string OPERATOR;
	static const string SPECIAL_CHARACTER;
};