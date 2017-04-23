#pragma once
#include <string>
#include "Printable.h"

using namespace std;

class ParserException: public exception {
public:
	explicit ParserException(char const* _Message);

	explicit ParserException(string& _Message);

	explicit ParserException(string const& _Message);

	explicit ParserException(Printable* printable);
};
