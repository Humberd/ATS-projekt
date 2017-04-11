#pragma once
#include <string>

using namespace std;

class SourceFileException: exception {
public:
	explicit SourceFileException(char const* _Message);

	explicit SourceFileException(string& _Message);

	explicit SourceFileException(string const& _Message);

};
