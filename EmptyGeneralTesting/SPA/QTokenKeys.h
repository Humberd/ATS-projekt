#pragma once
#include <string>

using namespace std;

class QTokenKeys {
private: 
	QTokenKeys();
	~QTokenKeys();

public:
	static const string DECLARATION_KEYWORD;
	static const string QUERY_KEYWORD;
	static const string QUERY_METHOD;
	static const string NAME;
	static const string INTEGER;
	static const string SPECIAL_CHARACTER;
};
