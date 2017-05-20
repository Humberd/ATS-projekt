#pragma once
#include <string>

using namespace std;

class QLexerException : exception {
public:
	explicit QLexerException(char const* _Message);

	explicit QLexerException(string& _Message);

	explicit QLexerException(string const& _Message);
};

