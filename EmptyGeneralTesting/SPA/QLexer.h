#pragma once
#include <vector>
#include "QLexerToken.h"

using namespace std;

class QLexer {
private: 
	QLexer();

public:
	~QLexer();

	static vector<QLexerToken*> parseDeclarations(string sourceDeclarations);
	static vector<QLexerToken*> parseQuery(string sourceQuery);

	static string scanName(string::iterator& iterator, string::iterator& endIterator);
	static string scanInteger(string::iterator& iterator, string::iterator& endIterator);
};