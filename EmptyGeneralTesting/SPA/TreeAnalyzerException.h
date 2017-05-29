#pragma once
#include <string>

using namespace std;

class TreeAnalyzerException: public exception {
public:
	explicit TreeAnalyzerException(char const* _Message);

	explicit TreeAnalyzerException(string& _Message);

	explicit TreeAnalyzerException(string const& _Message);
};
