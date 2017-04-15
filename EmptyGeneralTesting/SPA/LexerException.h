#pragma once
#include <exception>
#include <string>

using namespace std;

class LexerException: exception {
public:
	explicit LexerException(char const* _Message);

	explicit LexerException(string& _Message);

	explicit LexerException(string const& _Message);
};
