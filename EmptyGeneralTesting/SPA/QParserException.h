#pragma once
#include <string>

using namespace std;

class QParserException: exception {
public:
	explicit QParserException(char const* _Message);

	explicit QParserException(string& _Message);

	explicit QParserException(string const& _Message);
};
