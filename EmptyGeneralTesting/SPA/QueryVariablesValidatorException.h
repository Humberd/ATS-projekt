#pragma once
#include <string>

using namespace std;

class QueryVariablesValidatorException: exception {
public:
	explicit QueryVariablesValidatorException(char const* _Message);

	explicit QueryVariablesValidatorException(string& _Message);

	explicit QueryVariablesValidatorException(string const& _Message);
};