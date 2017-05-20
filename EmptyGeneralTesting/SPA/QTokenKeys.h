#pragma once
#include <stddef.h>
#include <string>

using namespace std;

class QTokenKeys {
private: 
	QTokenKeys();
	~QTokenKeys();

public:
	static const string KEYWORD;
	static const string NAME;
	static const string INTEGER;
	static const string OPERATOR;
	static const string SPECIAL_CHARACTER;
};
